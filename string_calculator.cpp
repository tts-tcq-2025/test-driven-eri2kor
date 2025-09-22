#include "string_calculator.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <iterator>

int StringCalculator::Add(const std::string &numbers) {
    size_t pos = 0;
    std::string delimiter_str = DetectDelimiter(numbers, pos);
    char delimiter_char = delimiter_str[0];
    std::string input = numbers.substr(pos);

    std::replace(input.begin(), input.end(), '\n', ',');
    if (delimiter_char != ',') {
        std::replace(input.begin(), input.end(), delimiter_char, ',');
    }

    return SumNumbers(ParseNumbers(Split(input, ',')));
}

// Detect delimiter, returns ',' if default
std::string StringCalculator::DetectDelimiter(const std::string &numbers, size_t &pos) {
    return numbers.substr(0, 2) == "//"
               ? (numbers[2] == '['
                      ? numbers.substr(3, numbers.find(']', 2) - 3)
                      : std::string(1, numbers[2]))
               : (pos = 0, std::string(","));
}

// Split using stringstream and iterators (no loops)
std::vector<std::string> StringCalculator::Split(const std::string &input, char delimiter) {
    std::stringstream ss(input);
    return std::vector<std::string>{std::istream_iterator<std::string, char>(ss),
                                    std::istream_iterator<std::string, char>()};
}

// Parse numbers: std::transform, std::copy_if, std::for_each
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

// Sum using accumulate
int StringCalculator::SumNumbers(const std::vector<int> &numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), 0);
}
