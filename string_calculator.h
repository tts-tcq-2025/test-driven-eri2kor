#pragma once
#include <string>
#include <vector>

class StringCalculator {
public:
    int Add(const std::string &numbers);

private:
    // Pure helpers
    static std::vector<std::string> Split(const std::string &str, const std::string &delimiter);
    static std::string DetectDelimiter(const std::string &numbers, size_t &pos);
    static std::vector<int> ParseNumbers(const std::vector<std::string> &tokens);
    static int SumNumbers(const std::vector<int> &numbers);
};
