#pragma once
#include <string>
#include <vector>
#include <utility>

class StringCalculator {
 public:
  int add(const std::string& input);

 private:
  std::pair<std::string, std::string> parseDelimiter(
      const std::string& input) const;
  std::vector<std::string> split(
      const std::string& numbers,
      const std::vector<std::string>& delimiters) const;
  int toInt(const std::string& token) const;
};
