#include "string_calculator.h"

#include <gtest/gtest.h>

TEST(StringCalculatorTest, EmptyStringReturnsZero) {
  StringCalculator calc;
  EXPECT_EQ(calc.add(""), 0);
}

TEST(StringCalculatorTest, SingleNumber) {
  StringCalculator calc;
  EXPECT_EQ(calc.add("5"), 5);
}

TEST(StringCalculatorTest, TwoNumbersCommaSeparated) {
  StringCalculator calc;
  EXPECT_EQ(calc.add("1,2"), 3);
}

TEST(StringCalculatorTest, UnknownAmountOfNumbers) {
  StringCalculator calc;
  EXPECT_EQ(calc.add("1,2,3,4,5"), 15);
}

TEST(StringCalculatorTest, NewLineBetweenNumbers) {
  StringCalculator calc;
  EXPECT_EQ(calc.add("1\n2,3"), 6);
}

TEST(StringCalculatorTest, CustomDelimiter) {
  StringCalculator calc;
  EXPECT_EQ(calc.add("//;\n1;2"), 3);
}

TEST(StringCalculatorTest, CustomDelimiterAnyLength) {
  StringCalculator calc;
  EXPECT_EQ(calc.add("//***\n1***2***3"), 6);
}

TEST(StringCalculatorTest, IgnoreNumbersGreaterThan1000) {
  StringCalculator calc;
  EXPECT_EQ(calc.add("2,1001"), 2);
  EXPECT_EQ(calc.add("1000,2"), 1002);
}

TEST(StringCalculatorTest, NegativeNumbersThrow) {
  StringCalculator calc;
  try {
    calc.add("1,-2,3,-4");
    FAIL() << "Expected exception";
  } catch (const std::runtime_error& e) {
    EXPECT_STREQ(e.what(), "negatives not allowed:-2,-4");
  }
}
