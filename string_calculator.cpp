#include "string_calculator.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

int StringCalculator::Add(const std::string &numbers) {
    if (numbers.empty()) {
        return 0;
    }

    size_t pos = 0;
    std::string delimiter = DetectDelimiter(numbers, pos);
    std::string input = numbers.substr(pos);

    // Normalize newlines
    std::replace(input.begin(), input.end(), '\n', ',');
    if (delimiter != ",") {
        size_t dlen = delimiter.length();
        size_t start = 0;
        while ((start = input.find(delimiter, start)) != std::string::npos) {
            input.replace(start, dlen, ",");
            start += 1;
        }
    }

    std::vector<std::string> tokens = Split(input, ",");
    int sum = 0;
    std::string negatives;

    for (const auto &token : tokens) {
        if (token.empty()) continue;
        int num = std::stoi(token);
        if (num < 0) {
            if (!negatives.empty()) negatives += ",";
            negatives += std::to_string(num);
        } else if (num <= 1000) {
            sum += num;
        }
    }

    if (!negatives.empty()) {
        throw std::runtime_error("negatives not allowed: " + negatives);
    }

    return sum;
}

// Pure function: split string by delimiter
std::vector<std::string> StringCalculator::Split(const std::string &str, const std::string &delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t dlen = delimiter.length();
    size_t pos = 0;
    while ((pos = str.find(delimiter, start)) != std::string::npos) {
        result.push_back(str.substr(start, pos - start));
        start = pos + dlen;
    }
    result.push_back(str.substr(start));
    return result;
}

// Pure function: detect custom delimiter
std::string StringCalculator::DetectDelimiter(const std::string &numbers, size_t &pos) {
    if (numbers.substr(0, 2) == "//") {
        size_t newline = numbers.find('\n');
        if (numbers[2] == '[') { // multi-character delimiter
            size_t end = numbers.find(']', 2);
            pos = newline + 1;
            return numbers.substr(3, end - 3);
        } else { // single-character delimiter
            pos = newline + 1;
            return std::string(1, numbers[2]);
        }
    }
    pos = 0;
    return ",";
}
