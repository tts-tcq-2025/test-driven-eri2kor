#include "string_calculator.h"

#include <sstream>
#include <stdexcept>

std::pair<std::string, std::string> StringCalculator::parseDelimiter(
    const std::string& input) const {
  if (input.rfind("//", 0) == 0) {
    size_t newlinePos = input.find('\n');
    return {input.substr(2, newlinePos - 2), input.substr(newlinePos + 1)};
  }
  return {",", input};
}

std::vector<std::string> StringCalculator::split(
    const std::string& numbers,
    const std::vector<std::string>& delimiters) const {
  std::vector<std::string> tokens;
  std::string token;
  size_t i = 0;
  while (i < numbers.size()) {
    bool matched = false;
    for (const auto& d : delimiters) {
      if (numbers.compare(i, d.size(), d) == 0) {
        if (!token.empty()) {
          tokens.push_back(token);
          token.clear();
        }
        i += d.size();
        matched = true;
        break;
      }
    }
    if (!matched) {
      token.push_back(numbers[i]);
      ++i;
    }
  }
  if (!token.empty()) {
    tokens.push_back(token);
  }
  return tokens;
}

int StringCalculator::toInt(const std::string& token) const {
  if (token.empty()) return 0;
  return std::stoi(token);
}

int StringCalculator::add(const std::string& input) {
  if (input.empty()) return 0;

  auto [delimiter, numbersPart] = parseDelimiter(input);
  std::vector<std::string> delimiters = {delimiter, "\n", ","};

  auto tokens = split(numbersPart, delimiters);

  std::vector<int> negatives;
  int sum = 0;
  for (const auto& t : tokens) {
    int num = toInt(t);
    if (num < 0) {
      negatives.push_back(num);
    } else if (num <= 1000) {
      sum += num;
    }
  }

  if (!negatives.empty()) {
    std::ostringstream oss;
    oss << "negatives not allowed:";
    for (size_t i = 0; i < negatives.size(); ++i) {
      if (i > 0) oss << ",";
      oss << negatives[i];
    }
    throw std::runtime_error(oss.str());
  }

  return sum;
}
