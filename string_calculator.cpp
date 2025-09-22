#include "string_calculator.h"
#include <regex>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <numeric>

int StringCalculator::Add(const std::string &numbers) {
    size_t pos = 0;
    std::string delimiter = DetectDelimiter(numbers, pos);
    std::string input = numbers.substr(pos);

    // Normalize newlines to comma
    std::replace(input.begin(), input.end(), '\n', ',');

    // Convert delimiter to regex string
    std::string delimiter_regex = delimiter == "," ? "," : std::regex_replace(delimiter, std::regex(R"([\^$.|?*+(){}\[\]])"), R"(\\$&)");

    return SumNumbers(ParseNumbers(Split(input, delimiter_regex)));
}

// Detect delimiter, default ','
std::string StringCalculator::DetectDelimiter(const std::string &numbers, size_t &pos) {
    return numbers.substr(0, 2) == "//"
               ? (numbers[2] == '['
                      ? numbers.substr(3, numbers.find(']', 2) - 3)
                      : std::string(1, numbers[2]))
               : (pos = 0, std::string(","));
}

// Split using regex (no loops), CCN = 0
std::vector<std::string> StringCalculator::Split(const std::string &input,
                                                 const std::string &delimiter_regex) {
    std::regex re(delimiter_regex);
    return std::vector<std::string>{std::sregex_token_iterator(input.begin(), input.end(), re, -1),
                                    std::sregex_token_iterator()};
}

// Parse numbers, throw negatives, ignore >1000 using STL
std::vector<int> StringCalculator::ParseNumbers(const std::vector<std::string> &tokens) {
    std::vector<int> numbers(tokens.size());
    std::transform(tokens.begin(), tokens.end(), numbers.begin(),
                   [](const std::string &t) { return t.empty() ? 0 : std::stoi(t); });

    std::string negatives;
    std::for_each(numbers.begin(), numbers.end(),
                  [&negatives](int n) { if (n < 0) negatives += (negatives.empty() ? "" : ",") + std::to_string(n); });

    if (!negatives.empty()) throw std::runtime_error("negatives not allowed: " + negatives);

    std::vector<int> filtered;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(filtered),
                 [](int n) { return n <= 1000; });
    return filtered;
}

// Sum using accumulate, CCN = 0
int StringCalculator::SumNumbers(const std::vector<int> &numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), 0);
}
