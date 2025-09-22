#include "StringCalculator.h"
#include <sstream>
#include <algorithm>
#include <regex>

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }
    
    std::string numbersOnly;
    std::string delimiter = extractDelimiter(numbers, numbersOnly);
    
    auto tokens = split(numbersOnly, delimiter);
    auto nums = parseNumbers(tokens);
    
    validateNumbers(nums);
    return sumValidNumbers(nums);
}

std::string StringCalculator::extractDelimiter(const std::string& numbers, std::string& numbersOnly) {
    if (numbers.length() < 2 || numbers.substr(0, 2) != "//") {
        numbersOnly = numbers;
        return ",|\n";
    }
    
    size_t newlinePos = numbers.find('\n');
    if (newlinePos == std::string::npos) {
        numbersOnly = numbers;
        return ",|\n";
    }
    
    std::string delimiterLine = numbers.substr(2, newlinePos - 2);
    numbersOnly = numbers.substr(newlinePos + 1);
    
    // Handle bracket format: [delimiter]
    if (delimiterLine.front() == '[' && delimiterLine.back() == ']') {
        return std::regex_escape(delimiterLine.substr(1, delimiterLine.length() - 2));
    }
    
    return std::regex_escape(delimiterLine);
}

std::vector<std::string> StringCalculator::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    std::regex delimiterRegex(delimiter);
    std::sregex_token_iterator iter(str.begin(), str.end(), delimiterRegex, -1);
    std::sregex_token_iterator end;
    
    for (; iter != end; ++iter) {
        std::string token = *iter;
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

std::vector<int> StringCalculator::parseNumbers(const std::vector<std::string>& tokens) {
    std::vector<int> nums;
    for (const auto& token : tokens) {
        try {
            nums.push_back(std::stoi(token));
        } catch (const std::exception&) {
            // Skip invalid numbers
        }
    }
    return nums;
}

void StringCalculator::validateNumbers(const std::vector<int>& nums) {
    std::vector<int> negatives;
    for (int num : nums) {
        if (num < 0) {
            negatives.push_back(num);
        }
    }
    
    if (!negatives.empty()) {
        std::stringstream ss;
        ss << "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << negatives[i];
        }
        throw NegativeNumberException(ss.str());
    }
}

int StringCalculator::sumValidNumbers(const std::vector<int>& nums) {
    int sum = 0;
    for (int num : nums) {
        if (num <= 1000) {
            sum += num;
        }
    }
    return sum;
}
