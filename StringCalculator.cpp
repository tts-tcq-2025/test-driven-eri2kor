#include "StringCalculator.h"
#include <regex>
#include <sstream>
#include <algorithm>

int StringCalculator::Add(const std::string& numbers) {
    if (isEmptyString(numbers)) {
        return 0;
    }
    
    const std::string delimiter = hasCustomDelimiter(numbers) ? 
        extractDelimiter(numbers) : ",|\n";
    const std::string numbersOnly = hasCustomDelimiter(numbers) ? 
        extractNumbersSection(numbers) : numbers;
    
    const auto tokens = tokenizeNumbers(numbersOnly, delimiter);
    const auto integers = convertToIntegers(tokens);
    validateNegativeNumbers(integers);
    return sumValidNumbers(integers);
}

bool StringCalculator::isEmptyString(const std::string& input) const {
    return input.empty();
}

bool StringCalculator::hasCustomDelimiter(const std::string& input) const {
    return input.length() >= 2 && input.substr(0, 2) == "//";
}

std::string StringCalculator::extractDelimiter(const std::string& input) const {
    const size_t newlinePos = input.find('\n');
    if (newlinePos == std::string::npos) {
        return ",|\n";
    }
    
    const std::string rawDelimiter = input.substr(2, newlinePos - 2);
    const std::string processedDelimiter = processDelimiterBrackets(rawDelimiter);
    return escapeSpecialCharacters(processedDelimiter);
}

std::string StringCalculator::extractNumbersSection(const std::string& input) const {
    const size_t newlinePos = input.find('\n');
    if (newlinePos == std::string::npos) {
        return "";
    }
    return input.substr(newlinePos + 1);
}

std::string StringCalculator::processDelimiterBrackets(const std::string& delimiter) const {
    if (delimiter.length() >= 2 && delimiter.front() == '[' && delimiter.back() == ']') {
        return delimiter.substr(1, delimiter.length() - 2);
    }
    return delimiter;
}

std::string StringCalculator::escapeSpecialCharacters(const std::string& delimiter) const {
    return std::regex_replace(delimiter, std::regex(R"([\[\]{}()*+?.^$|\\])"), R"(\$&)");
}

std::vector<std::string> StringCalculator::tokenizeNumbers(const std::string& numbers, const std::string& delimiter) const {
    std::vector<std::string> result;
    const std::regex delimiterRegex(delimiter);
    std::sregex_token_iterator iter(numbers.begin(), numbers.end(), delimiterRegex, -1);
    const std::sregex_token_iterator end;
    
    for (; iter != end; ++iter) {
        if (!iter->str().empty()) {
            result.push_back(iter->str());
        }
    }
    return result;
}

std::vector<int> StringCalculator::convertToIntegers(const std::vector<std::string>& tokens) const {
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

void StringCalculator::validateNegativeNumbers(const std::vector<int>& numbers) const {
    std::vector<int> negatives;
    for (const int number : numbers) {
        if (number < 0) {
            negatives.push_back(number);
        }
    }
    
    if (!negatives.empty()) {
        throw NegativeNumberException(createNegativeErrorMessage(negatives));
    }
}

std::string StringCalculator::createNegativeErrorMessage(const std::vector<int>& negatives) const {
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

int StringCalculator::sumValidNumbers(const std::vector<int>& numbers) const {
    int sum = 0;
    for (const int number : numbers) {
        if (number <= 1000) {
            sum += number;
        }
    }
    return sum;
}
