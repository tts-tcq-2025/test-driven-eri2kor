#include "StringCalculator.h"
#include <sstream>
#include <regex>

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }
    
    std::string delimiter = hasCustomDelimiter(numbers) ? 
        extractCustomDelimiter(numbers) : ",|\n";
    std::string numbersOnly = hasCustomDelimiter(numbers) ? 
        extractNumbers(numbers) : numbers;
    
    auto tokens = splitByDelimiter(numbersOnly, getDelimiterPattern(delimiter));
    auto nums = convertToIntegers(tokens);
    checkForNegatives(nums);
    return sumNumbers(nums);
}

bool StringCalculator::hasCustomDelimiter(const std::string& numbers) {
    return numbers.length() >= 2 && numbers.substr(0, 2) == "//";
}

std::string StringCalculator::extractCustomDelimiter(const std::string& numbers) {
    size_t newlinePos = numbers.find('\n');
    if (newlinePos == std::string::npos) {
        return ",|\n";
    }
    return numbers.substr(2, newlinePos - 2);
}

std::string StringCalculator::extractNumbers(const std::string& numbers) {
    size_t newlinePos = numbers.find('\n');
    if (newlinePos == std::string::npos) {
        return "";
    }
    return numbers.substr(newlinePos + 1);
}

std::string StringCalculator::getDelimiterPattern(const std::string& delimiter) {
    if (delimiter.empty()) {
        return ",|\n";
    }
    
    if (delimiter.front() == '[' && delimiter.back() == ']') {
        std::string inner = delimiter.substr(1, delimiter.length() - 2);
        return std::regex_replace(inner, std::regex(R"([\^\$\.\*\+\?\(\)\[\]\{\}\|\\])"), R"(\$&)");
    }
    
    return std::regex_replace(delimiter, std::regex(R"([\^\$\.\*\+\?\(\)\[\]\{\}\|\\])"), R"(\$&)");
}

std::vector<std::string> StringCalculator::splitByDelimiter(const std::string& str, const std::string& pattern) {
    std::vector<std::string> tokens;
    std::regex delimiterRegex(pattern);
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

std::vector<int> StringCalculator::convertToIntegers(const std::vector<std::string>& tokens) {
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

void StringCalculator::checkForNegatives(const std::vector<int>& numbers) {
    std::vector<int> negatives;
    for (int num : numbers) {
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

int StringCalculator::sumNumbers(const std::vector<int>& numbers) {
    int sum = 0;
    for (int num : numbers) {
        if (isValidNumber(num)) {
            sum += num;
        }
    }
    return sum;
}

bool StringCalculator::isValidNumber(int number) {
    return number >= 0 && number <= 1000;
}
