#include "StringCalculator.h"
#include <sstream>
#include <regex>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>

int StringCalculator::add(const std::string& input) {
    if (input.empty()) return 0;

    std::string numbers = input;
    std::string delimiterPattern = ",|\n"; // default delimiters

    // Check for custom delimiter
    if (numbers.rfind("//", 0) == 0) { // starts with "//"
        size_t newlinePos = numbers.find("\n");
        std::string header = numbers.substr(2, newlinePos - 2);
        numbers = numbers.substr(newlinePos + 1);

        // Handle delimiters in brackets [***]
        if (header.front() == '[' && header.back() == ']') {
            delimiterPattern = std::regex_replace(header.substr(1, header.size() - 2), std::regex(R"([\^$.|?*+(){}\\])"), R"(\\$&)");
        } else {
            delimiterPattern = std::regex_replace(header, std::regex(R"([\^$.|?*+(){}\\])"), R"(\\$&)");
        }
    }

    // Split numbers using regex
    std::regex re(delimiterPattern);
    std::sregex_token_iterator it(numbers.begin(), numbers.end(), re, -1);
    std::sregex_token_iterator end;

    std::vector<int> nums;
    for (; it != end; ++it) {
        if (!it->str().empty()) {
            int n = std::stoi(it->str());
            nums.push_back(n);
        }
    }

    // Check for negatives
    std::vector<int> negatives;
    for (int n : nums) {
        if (n < 0) negatives.push_back(n);
    }
    if (!negatives.empty()) {
        std::string msg = "negatives not allowed:";
        for (int n : negatives) msg += " " + std::to_string(n);
        throw std::runtime_error(msg);
    }

    // Sum numbers ≤ 1000
    int total = 0;
    for (int n : nums) {
        if (n <= 1000) total += n;
    }

    return total;
}
