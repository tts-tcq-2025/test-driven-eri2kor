#include <gtest/gtest.h>
#include "StringCalculator.h"

class StringCalculatorTest : public ::testing::Test {
protected:
    StringCalculator calculator;
};

// TDD Step 1: Smallest failing test
TEST_F(StringCalculatorTest, EmptyStringReturnsZero) {
    EXPECT_EQ(0, calculator.Add(""));
}

// TDD Step 2: Single number
TEST_F(StringCalculatorTest, SingleNumberReturnsThatNumber) {
    EXPECT_EQ(1, calculator.Add("1"));
    EXPECT_EQ(5, calculator.Add("5"));
}

// TDD Step 3: Two numbers
TEST_F(StringCalculatorTest, TwoNumbersReturnSum) {
    EXPECT_EQ(3, calculator.Add("1,2"));
    EXPECT_EQ(10, calculator.Add("4,6"));
}

// TDD Step 4: Unknown amount of numbers
TEST_F(StringCalculatorTest, UnknownAmountOfNumbers) {
    EXPECT_EQ(6, calculator.Add("1,2,3"));
    EXPECT_EQ(15, calculator.Add("1,2,3,4,5"));
}

// TDD Step 5: Newline delimiters
TEST_F(StringCalculatorTest, NewLineDelimiters) {
    EXPECT_EQ(6, calculator.Add("1\n2,3"));
    EXPECT_EQ(6, calculator.Add("1,2\n3"));
}

// TDD Step 6: Custom delimiters
TEST_F(StringCalculatorTest, CustomDelimiters) {
    EXPECT_EQ(3, calculator.Add("//;\n1;2"));
    EXPECT_EQ(6, calculator.Add("//|\n1|2|3"));
}

// TDD Step 7: Negative numbers
TEST_F(StringCalculatorTest, NegativeNumbersThrowException) {
    EXPECT_THROW(calculator.Add("1,-2,3"), NegativeNumberException);
}

TEST_F(StringCalculatorTest, MultipleNegativeNumbersShowAllInMessage) {
    try {
        calculator.Add("1,-2,-3,4");
        FAIL() << "Expected NegativeNumberException";
    } catch (const NegativeNumberException& e) {
        EXPECT_STREQ("negatives not allowed: -2, -3", e.what());
    }
}

// TDD Step 8: Numbers bigger than 1000
TEST_F(StringCalculatorTest, NumbersBiggerThanThousandIgnored) {
    EXPECT_EQ(2, calculator.Add("2,1001"));
    EXPECT_EQ(1000, calculator.Add("1000,1001"));
}

// TDD Step 9: Delimiters of any length
TEST_F(StringCalculatorTest, DelimitersOfAnyLength) {
    EXPECT_EQ(6, calculator.Add("//[***]\n1***2***3"));
    EXPECT_EQ(6, calculator.Add("//[||]\n1||2||3"));
}

// Edge cases for 100% coverage
TEST_F(StringCalculatorTest, EdgeCases) {
    EXPECT_EQ(0, calculator.Add("0"));
    EXPECT_EQ(999, calculator.Add("999"));
    EXPECT_EQ(3, calculator.Add("1,abc,2"));
    EXPECT_EQ(0, calculator.Add("//;\n"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
