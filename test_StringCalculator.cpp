#include "gtest/gtest.h"
#include "StringCalculator.h"

TEST(StringCalculatorTest, EmptyStringReturnsZero) {
    StringCalculator calc;
    EXPECT_EQ(calc.add(""), 0);
}

TEST(StringCalculatorTest, SingleNumber) {
    StringCalculator calc;
    EXPECT_EQ(calc.add("1"), 1);
}

TEST(StringCalculatorTest, TwoNumbers) {
    StringCalculator calc;
    EXPECT_EQ(calc.add("1,2"), 3);
}

TEST(StringCalculatorTest, NewlineDelimiter) {
    StringCalculator calc;
    EXPECT_EQ(calc.add("1\n2,3"), 6);
}

TEST(StringCalculatorTest, CustomDelimiter) {
    StringCalculator calc;
    EXPECT_EQ(calc.add("//;\n1;2"), 3);
}

TEST(StringCalculatorTest, NegativeNumbersThrow) {
    StringCalculator calc;
    EXPECT_THROW({
        try {
            calc.add("1,-2,3,-4");
        } catch (const std::invalid_argument& e) {
            EXPECT_STREQ("negatives not allowed: -2 -4", e.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(StringCalculatorTest, NumbersGreaterThan1000Ignored) {
    StringCalculator calc;
    EXPECT_EQ(calc.add("2,1001"), 2);
}

TEST(StringCalculatorTest, DelimiterOfAnyLength) {
    StringCalculator calc;
    EXPECT_EQ(calc.add("//[***]\n1***2***3"), 6);
}

TEST(StringCalculatorTest, MultipleDelimiters) {
    StringCalculator calc;
    EXPECT_EQ(calc.add("//[*][%]\n1*2%3"), 6);
}

TEST(StringCalculatorTest, MultipleDelimitersOfDifferentLength) {
    StringCalculator calc;
    EXPECT_EQ(calc.add("//[***][%%]\n1***2%%3"), 6);
}
