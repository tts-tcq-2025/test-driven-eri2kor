#include "StringCalculator.h"
#include <regex>
#include <sstream>
#include <algorithm>

int StringCalculator::Add(const std::string& numbers) {
    if (isEmptyInput(numbers)) {
        return 0;
    }
    
    std::string delimiter = hasCustomDelimiter(numbers) ? 
        extractDelimiter(numbers) : ",|\n";
    std::string numbersOnly = hasCustomDelimiter(numbers) ? 
        extractNumbers(numbers) : numbers;
    
    auto tokens = splitNumbers(numbersOnly, delimiter);
    auto parsedNumbers = parseNumbers(tokens);
    validateNoNegatives(parsedNumbers);
    return calculateSum(parsedNumbers);
}

bool StringCalculator::isEmptyInput(const std::string& input) {
    return input.empty();
}

bool StringCalculator::hasCustomDelimiter(const std::string& input) {
    return input.length() >= 2 && input.substr(0, 2) == "//";
}

std::string StringCalculator::extractDelimiter(const std::string& input) {
    size_t newlinePos = input.find('\n');
    if (newlinePos == std::string::npos) {
        return ",|\n";
    }
    
    std::string delimiterPart = input.substr(2, newlinePos - 2);
    if (delimiterPart.front() == '[' && delimiterPart.back() == ']') {
        delimiterPart = delimiterPart.substr(1, delimiterPart.length() - 2);
    }
    
    return std::regex_replace(delimiterPart, std::regex(R"([\[\]{}()*+?.^$|\\])"), R"(\$&)");
}

std::string StringCalculator::extractNumbers(const std::string& input) {
    size_t newlinePos = input.find('\n');
    if (newlinePos == std::string::npos) {
        return "";
    }
    return input.substr(newlinePos + 1);
}

std::vector<std::string> StringCalculator::splitNumbers(const std::string& numbers, const std::string& delimiter) {
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

std::vector<int> StringCalculator::parseNumbers(const std::vector<std::string>& tokens) {
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

void StringCalculator::validateNoNegatives(const std::vector<int>& numbers) {
    std::vector<int> negatives;
    for (int number : numbers) {
        if (number < 0) {
            negatives.push_back(number);
        }
    }
    
    if (!negatives.empty()) {
        std::ostringstream message;
        message << "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i > 0) {
                message << ", ";
            }
            message << negatives[i];
        }
        throw NegativeNumberException(message.str());
    }
}

int StringCalculator::calculateSum(const std::vector<int>& numbers) {
    int sum = 0;
    for (int number : numbers) {
        if (number <= 1000) {
            sum += number;
        }
    }
    return sum;
}
