#include "string_calculator.h"
#include <gtest/gtest.h>

TEST(StringCalculatorTest, EmptyStringReturnsZero) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add(""), 0);
}

TEST(StringCalculatorTest, SingleNumber) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("5"), 5);
}

TEST(StringCalculatorTest, TwoNumbersCommaSeparated) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("1,2"), 3);
}

TEST(StringCalculatorTest, UnknownAmountOfNumbers) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("1,2,3,4,5"), 15);
}

TEST(StringCalculatorTest, NewLineBetweenNumbers) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("1\n2,3"), 6);
}

TEST(StringCalculatorTest, CustomDelimiter) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("//;\n1;2"), 3);
}

TEST(StringCalculatorTest, CustomDelimiterAnyLength) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("//***\n1***2***3"), 6);
}

TEST(StringCalculatorTest, IgnoreNumbersGreaterThan1000) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("2,1001"), 2);
    EXPECT_EQ(calc.Add("1000,2"), 1002);
}

TEST(StringCalculatorTest, NegativeNumbersThrow) {
    StringCalculator calc;
    try {
        calc.Add("1,-2,3,-4");
        FAIL() << "Expected exception";
    } catch (std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "negatives not allowed:-2,-4");
    }
}
