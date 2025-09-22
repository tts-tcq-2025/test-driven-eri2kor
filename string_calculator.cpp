#include "string_calculator.h"
#include <algorithm>
#include <stdexcept>

int StringCalculator::Add(const std::string &numbers) {
    size_t pos = 0;
    std::string delimiter = DetectDelimiter(numbers, pos);
    std::string input = numbers.substr(pos);
    std::replace(input.begin(), input.end(), '\n', ',');
    if (delimiter != ",") {
        size_t start = 0;
        while ((start = input.find(delimiter, start)) != std::string::npos) {
            input.replace(start, delimiter.length(), ",");
            start += 1;
        }
    }
    return SumNumbers(ParseNumbers(Split(input, ","))); // one-line orchestrator
}

// Detect custom delimiter, returns ',' if default
std::string StringCalculator::DetectDelimiter(const std::string &numbers, size_t &pos) {
    if (numbers.substr(0, 2) != "//") {
        pos = 0;
        return ",";
    }
    size_t newline = numbers.find('\n');
    if (numbers[2] == '[') { // multi-character
        size_t end = numbers.find(']', 2);
        pos = newline + 1;
        return numbers.substr(3, end - 3);
    }
    pos = newline + 1; // single-character
    return std::string(1, numbers[2]);
}

// Split string by delimiter (pure)
std::vector<std::string> StringCalculator::Split(const std::string &str,
                                                 const std::string &delimiter) {
    std::vector<std::string> result;
    size_t start = 0, pos = 0, dlen = delimiter.length();
    while ((pos = str.find(delimiter, start)) != std::string::npos) {
        result.push_back(str.substr(start, pos - start));
        start = pos + dlen;
    }
    result.push_back(str.substr(start));
    return result;
}

// Parse tokens into integers, throws if negative, ignores >1000
std::vector<int> StringCalculator::ParseNumbers(const std::vector<std::string> &tokens) {
    std::vector<int> numbers;
    std::string negatives;
    for (const std::string &token : tokens) {
        if (token.empty()) continue;
        int num = std::stoi(token);
        if (num < 0) {
            if (!negatives.empty()) negatives += ",";
            negatives += std::to_string(num);
        } else if (num <= 1000) {
            numbers.push_back(num);
        }
    }
    if (!negatives.empty()) {
        throw std::runtime_error("negatives not allowed: " + negatives);
    }
    return numbers;
}

// Sum all numbers (pure)
int StringCalculator::SumNumbers(const std::vector<int> &numbers) {
    int sum = 0;
    for (int n : numbers) sum += n;
    return sum;
}
