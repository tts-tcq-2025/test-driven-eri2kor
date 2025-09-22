#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>

class StringCalculator {
public:
    int Add(const std::string& numbers);

private:
    bool isEmptyInput(const std::string& input);
    bool hasCustomDelimiter(const std::string& input);
    std::string extractDelimiter(const std::string& input);
    std::string extractNumbers(const std::string& input);
    std::vector<std::string> splitNumbers(const std::string& numbers, const std::string& delimiter);
    std::vector<int> parseNumbers(const std::vector<std::string>& tokens);
    void validateNoNegatives(const std::vector<int>& numbers);
    int calculateSum(const std::vector<int>& numbers);
};

class NegativeNumberException : public std::runtime_error {
public:
    explicit NegativeNumberException(const std::string& message) 
        : std::runtime_error(message) {}
};

#endif // STRING_CALCULATOR_H
