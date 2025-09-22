#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>

class StringCalculator {
public:
    int Add(const std::string& numbers);

private:
    bool hasCustomDelimiter(const std::string& numbers);
    std::string extractCustomDelimiter(const std::string& numbers);
    std::string extractNumbers(const std::string& numbers);
    std::string getDelimiterPattern(const std::string& delimiter);
    std::vector<std::string> splitByDelimiter(const std::string& str, const std::string& pattern);
    std::vector<int> convertToIntegers(const std::vector<std::string>& tokens);
    void checkForNegatives(const std::vector<int>& numbers);
    int sumNumbers(const std::vector<int>& numbers);
    bool isValidNumber(int number);
};

class NegativeNumberException : public std::runtime_error {
public:
    explicit NegativeNumberException(const std::string& message) 
        : std::runtime_error(message) {}
};

#endif // STRING_CALCULATOR_H
