#pragma once
#include <string>
#include <vector>

class StringCalculator {
public:
    int add(const std::string& numbers);

private:
    std::vector<std::string> splitNumbers(const std::string& numbers);
};
