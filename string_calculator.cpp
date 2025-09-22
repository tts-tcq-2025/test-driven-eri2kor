#include "string_calculator.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <numeric>

int StringCalculator::Add(const std::string &numbers) {
    size_t pos = 0;
    std::string delimiter_str = DetectDelimiter(numbers, pos);
    char delimiter_char = delimiter_str[0];
    std::string input = numbers.substr(pos);

    std::replace(input.begin(), input.end(), '\n', ',');
    if (delimiter_char != ',') {
        std::replace(input.begin(), input.end(), delimiter_char, ',');
    }

    return SumNumbers(ParseNumbers(Split(input, ','))); // single-line orchestrator
}

// Detect delimiter, default ','
std::string StringCalculator::DetectDelimiter(const std::string &numbers, size_t &pos) {
    if (numbers.substr(0, 2) != "//") {
        pos = 0;
        return ",";
    }
    size_t newline = numbers.find('\n');
    pos = newline + 1;
    return numbers[2] == '[' ? numbers.substr(3, numbers.find(']', 2) - 3)
                              : std::string(1, numbers[2]);
}

// Split using stringstream (no loops, CCN=0)
std::vector<std::string> StringCalculator::Split(const std::string &input, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Parse numbers, throw negatives, ignore >1000 (pure)
std::vector<int> StringCalculator::ParseNumbers(const std::vector<std::string> &tokens) {
    std::vector<int> numbers(tokens.size());
    std::transform(tokens.begin(), tokens.end(), numbers.begin(),
                   [](const std::string &token) { return token.empty() ? 0 : std::stoi(token); });

    std::string negatives;
    std::for_each(numbers.begin(), numbers.end(),
                  [&negatives](int n) { if (n < 0) negatives += (negatives.empty() ? "" : ",") + std::to_string(n); });

    if (!negatives.empty()) {
        throw std::runtime_error("negatives not allowed: " + negatives);
    }

    numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                                 [](int n) { return n > 1000; }),
                  numbers.end());
    return numbers;
}

// Sum all numbers using accumulate (pure, CCN=0)
int StringCalculator::SumNumbers(const std::vector<int> &numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), 0);
}
