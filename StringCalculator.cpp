#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <vector>
#include <regex>

std::vector<std::string> StringCalculator::splitNumbers(const std::string& numbers) {
    if (numbers.empty()) return {};

    std::string nums = numbers;
    std::vector<std::string> delimiters = {",", "\n"};

    // Custom delimiter section
    if (nums.rfind("//", 0) == 0) {
        auto pos = nums.find("\n");
        std::string header = nums.substr(2, pos - 2);
        nums = nums.substr(pos + 1);

        // Look for delimiters in []
        std::regex bracketed("\\[(.*?)\\]");
        std::smatch match;
        std::string::const_iterator searchStart(header.cbegin());

        while (std::regex_search(searchStart, header.cend(), match, bracketed)) {
            delimiters.push_back(match[1].str());
            searchStart = match.suffix().first;
        }

        // If no [] found, single delimiter
        if (delimiters.size() == 2) {
            delimiters.push_back(header);
        }
    }

    // Build regex (escape special chars properly)
    std::string pattern;
    for (size_t i = 0; i < delimiters.size(); ++i) {
        if (i > 0) pattern += "|";
        pattern += "(" + std::regex_replace(delimiters[i],
                     std::regex(R"([-[\]{}()*+?.,\^$|#\s])"), R"(\$&)") + ")";
    }

    std::regex re(pattern);
    std::sregex_token_iterator it(nums.begin(), nums.end(), re, -1), end;

    std::vector<std::string> tokens;
    for (; it != end; ++it) {
        if (!it->str().empty()) tokens.push_back(it->str());
    }

    return tokens;
}

int StringCalculator::add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    auto tokens = splitNumbers(numbers);
    int sum = 0;
    std::vector<int> negatives;

    for (auto& token : tokens) {
        int n = std::stoi(token);
        if (n < 0) negatives.push_back(n);
        else if (n <= 1000) sum += n;
    }

    if (!negatives.empty()) {
        std::string msg = "negatives not allowed:";
        for (int n : negatives) msg += " " + std::to_string(n);
        throw std::invalid_argument(msg);
    }

    return sum;
}
