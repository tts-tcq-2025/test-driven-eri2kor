#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>

class StringCalculator {
public:
    int Add(const std::string& numbers);

private:
    // CCN=1 functions for simple operations
    bool isEmptyInput(const std::string& input) const;
    bool hasCustomDelimiter(const std::string& input) const;
    std::string extractDelimiterSection(const std::string& input) const;
    std::string extractNumbersSection(const std::string& input) const;
    
    // CCN=2 functions for parsing
    std::string processDelimiterBrackets(const std::string& delimiter) const;
    std::string escapeRegexCharacters(const std::string& delimiter) const;
    std::vector<std::string> parseTokens(const std::string& numbers, const std::string& delimiter) const;
    
    // CCN=2 functions for validation and calculation
    std::vector<int> convertToNumbers(const std::vector<std::string>& tokens) const;
    void validateNoNegatives(const std::vector<int>& numbers) const;
    int sumValidNumbers(const std::vector<int>& numbers) const;
    
    // CCN=1 helper functions
    std::string formatNegativeMessage(const std::vector<int>& negatives) const;
    bool isValidNumber(int number) const;
};

class NegativeNumberException : public std::runtime_error {
public:
    explicit NegativeNumberException(const std::string& message) 
        : std::runtime_error(message) {}
};

#endif // STRING_CALCULATOR_H
