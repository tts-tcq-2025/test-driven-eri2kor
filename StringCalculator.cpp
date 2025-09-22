#include "StringCalculator.h"
#include <regex>
#include <stdexcept>

// Extract delimiters from header like [***][%%]
std::vector<std::string> StringCalculator::extractCustomDelimiters(const std::string& header) {
    std::vector<std::string> delimiters;
    std::regex bracketed("\\[(.*?)\\]");
    std::smatch match;
    auto start = header.cbegin();

    while (std::regex_search(start, header.cend(), match, bracketed)) {
        delimiters.push_back(match[1].str());
        start = match.suffix().first;
    }

    // No [] → single delimiter
    if (delimiters.empty() && !header.empty()) {
        delimiters.push_back(header);
    }
    return delimiters;
}

// Escape regex special chars and build union pattern
std::string StringCalculator::buildRegexPattern(const std::vector<std::string>& delimiters) {
    std::string pattern;
    for (size_t i = 0; i < delimiters.size(); ++i) {
        if (i > 0) pattern += "|";
        pattern += "(" + std::regex_replace(delimiters[i],
                     std::regex(R"([-[\]{}()*+?.,\^$|#\s])"), R"(\$&)") + ")";
    }
    return pattern;
}

// Split numbers using regex
std::vector<std::string> StringCalculator::tokenizeNumbers(const std::string& nums, const std::string& pattern) {
    std::regex re(pattern);
    std::sregex_token_iterator it(nums.begin(), nums.end(), re, -1), end;

    std::vector<std::string> tokens;
    for (; it != end; ++it) {
        if (!it->str().empty()) tokens.push_back(it->str());
    }
    return tokens;
}

std::vector<std::string> StringCalculator::splitNumbers(const std::string& numbers) {
    if (numbers.empty()) return {};

    std::string nums = numbers;
    std::vector<std::string> delimiters = {",", "\n"};

    if (nums.rfind("//", 0) == 0) {
        auto pos = nums.find("\n");
        auto header = nums.substr(2, pos - 2);
        nums = nums.substr(pos + 1);

        auto custom = extractCustomDelimiters(header);
        delimiters.insert(delimiters.end(), custom.begin(), custom.end());
    }

    return tokenizeNumbers(nums, buildRegexPattern(delimiters));
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
