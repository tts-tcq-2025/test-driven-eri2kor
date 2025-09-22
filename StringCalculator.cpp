#include "StringCalculator.h"
#include <regex>
#include <sstream>
#include <algorithm>

// Main Add method - CCN=3
int StringCalculator::Add(const std::string& numbers) {
    if (isEmptyInput(numbers)) {
        return 0;
    }
    
    std::string delimiter = hasCustomDelimiter(numbers) ? 
        extractDelimiterSection(numbers) : ",|\n";
    std::string numbersOnly = hasCustomDelimiter(numbers) ? 
        extractNumbersSection(numbers) : numbers;
    
    auto tokens = parseTokens(numbersOnly, delimiter);
    auto nums = convertToNumbers(tokens);
    validateNoNegatives(nums);
    return sumValidNumbers(nums);
}

// CCN=1: Simple empty check
bool StringCalculator::isEmptyInput(const std::string& input) const {
    return input.empty();
}

// CCN=1: Simple prefix check
bool StringCalculator::hasCustomDelimiter(const std::string& input) const {
    return input.length() >= 2 && input.substr(0, 2) == "//";
}

// CCN=2: Extract delimiter with fallback
std::string StringCalculator::extractDelimiterSection(const std::string& input) const {
    size_t newlinePos = input.find('\n');
    if (newlinePos == std::string::npos) {
        return ",|\n";
    }
    
    std::string rawDelimiter = input.substr(2, newlinePos - 2);
    std::string processedDelimiter = processDelimiterBrackets(rawDelimiter);
    return escapeRegexCharacters(processedDelimiter);
}

// CCN=2: Extract numbers section with fallback
std::string StringCalculator::extractNumbersSection(const std::string& input) const {
    size_t newlinePos = input.find('\n');
    if (newlinePos == std::string::npos) {
        return "";
    }
    return input.substr(newlinePos + 1);
}

// CCN=2: Process bracket notation
std::string StringCalculator::processDelimiterBrackets(const std::string& delimiter) const {
    if (delimiter.length() >= 2 && delimiter.front() == '[' && delimiter.back() == ']') {
        return delimiter.substr(1, delimiter.length() - 2);
    }
    return delimiter;
}

// CCN=1: Escape regex special characters
std::string StringCalculator::escapeRegexCharacters(const std::string& delimiter) const {
    return std::regex_replace(delimiter, std::regex(R"([\[\]{}()*+?.^$|\\])"), R"(\$&)");
}

// CCN=1: Parse tokens using regex
std::vector<std::string> StringCalculator::parseTokens(const std::string& numbers, const std::string& delimiter) const {
    std::vector<std::string> result;
    std::regex delimiterRegex(delimiter);
    std::sregex_token_iterator iter(numbers.begin(), numbers.end(), delimiterRegex, -1);
    std::sregex_token_iterator end;
    
    for (; iter != end; ++iter) {
        if (!iter->str().empty()) {
            result.push_back(iter->str());
        }
    }
    return result;
}

// CCN=2: Convert tokens to numbers with error handling
std::vector<int> StringCalculator::convertToNumbers(const std::vector<std::string>& tokens) const {
    std::vector<int> result;
    for (const auto& token : tokens) {
        try {
            result.push_back(std::stoi(token));
        } catch (const std::exception&) {
            // Skip invalid numbers
        }
    }
    return result;
}

// CCN=2: Validate no negatives and throw if found
void StringCalculator::validateNoNegatives(const std::vector<int>& numbers) const {
    std::vector<int> negatives;
    for (int number : numbers) {
        if (number < 0) {
            negatives.push_back(number);
        }
    }
    
    if (!negatives.empty()) {
        throw NegativeNumberException(formatNegativeMessage(negatives));
    }
}

// CCN=1: Format negative numbers error message
std::string StringCalculator::formatNegativeMessage(const std::vector<int>& negatives) const {
    std::ostringstream message;
    message << "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        if (i > 0) {
            message << ", ";
        }
        message << negatives[i];
    }
    return message.str();
}

// CCN=2: Sum only valid numbers (<=1000)
int StringCalculator::sumValidNumbers(const std::vector<int>& numbers) const {
    int sum = 0;
    for (int number : numbers) {
        if (isValidNumber(number)) {
            sum += number;
        }
    }
    return sum;
}

// CCN=1: Check if number is valid (non-negative and <=1000)
bool StringCalculator::isValidNumber(int number) const {
    return number >= 0 && number <= 1000;
}
