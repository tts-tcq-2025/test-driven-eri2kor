#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>

class StringCalculator {
public:
    int Add(const std::string& numbers);

private:
    std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    std::string extractDelimiter(const std::string& numbers, std::string& numbersOnly);
    void validateNumbers(const std::vector<int>& nums);
    int sumValidNumbers(const std::vector<int>& nums);
    std::vector<int> parseNumbers(const std::vector<std::string>& tokens);
};

class NegativeNumberException : public std::runtime_error {
public:
    explicit NegativeNumberException(const std::string& message) 
        : std::runtime_error(message) {}
};

#endif // STRING_CALCULATOR_H
