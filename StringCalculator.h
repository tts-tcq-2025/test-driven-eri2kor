#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>

class StringCalculator {
public:
    int Add(const std::string& numbers);

private:
    bool isEmptyString(const std::string& input) const;
    bool hasCustomDelimiter(const std::string& input) const;
    std::string extractDelimiter(const std::string& input) const;
    std::string extractNumbersSection(const std::string& input) const;
    std::vector<std::string> tokenizeNumbers(const std::string& numbers, const std::string& delimiter) const;
    std::vector<int> convertToIntegers(const std::vector<std::string>& tokens) const;
    void validateNegativeNumbers(const std::vector<int>& numbers) const;
    int sumValidNumbers(const std::vector<int>& numbers) const;
    std::string createNegativeErrorMessage(const std::vector<int>& negatives) const;
    std::string processDelimiterBrackets(const std::string& delimiter) const;
    std::string escapeSpecialCharacters(const std::string& delimiter) const;
};

class NegativeNumberException : public std::runtime_error {
public:
    explicit NegativeNumberException(const std::string& message) 
        : std::runtime_error(message) {}
};

#endif // STRING_CALCULATOR_H
