#pragma once
#include <string>
#include <vector>

class StringCalculator {
public:
    int add(const std::string& numbers);

private:
    std::vector<std::string> splitNumbers(const std::string& numbers);
    std::vector<std::string> extractCustomDelimiters(const std::string& header);
    std::string buildRegexPattern(const std::vector<std::string>& delimiters);
    std::vector<std::string> tokenizeNumbers(const std::string& nums, const std::string& pattern);
};
