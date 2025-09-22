#include <gtest/gtest.h>
#include "string_calculator.h"

TEST(StringCalculator, EmptyStringReturnsZero) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add(""), 0);
}

TEST(StringCalculator, SingleNumber) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("1"), 1);
}

TEST(StringCalculator, TwoNumbersCommaDelimited) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("1,2"), 3);
}

TEST(StringCalculator, HandlesNewlinesBetweenNumbers) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("1\n2,3"), 6);
}

TEST(StringCalculator, IgnoresNumbersBiggerThan1000) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("2,1001"), 2);
}

TEST(StringCalculator, CustomSingleCharacterDelimiter) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("//;\n1;2"), 3);
}

TEST(StringCalculator, CustomMultiCharacterDelimiter) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("//[***]\n1***2***3"), 6);
}

TEST(StringCalculator, ThrowsOnNegativeNumbers) {
    StringCalculator calc;
    try {
        calc.Add("1,-2,3,-4");
        FAIL() << "Expected std::runtime_error";
    } catch (std::runtime_error &e) {
        EXPECT_EQ(std::string(e.what()), "negatives not allowed: -2,-4");
    }
}
