#include <gtest/gtest.h>
#include "StringCalculator.h"

class StringCalculatorTest : public ::testing::Test {
protected:
    StringCalculator calculator;
};

// TDD Step 1: Smallest possible failing test
TEST_F(StringCalculatorTest, EmptyStringReturnsZero) {
    EXPECT_EQ(0, calculator.Add(""));
}

// TDD Step 2: Single number
TEST_F(StringCalculatorTest, SingleNumberReturnsThatNumber) {
    EXPECT_EQ(1, calculator.Add("1"));
    EXPECT_EQ(5, calculator.Add("5"));
    EXPECT_EQ(0, calculator.Add("0"));
}

// TDD Step 3: Two numbers
TEST_F(StringCalculatorTest, TwoNumbersReturnSum) {
    EXPECT_EQ(3, calculator.Add("1,2"));
    EXPECT_EQ(10, calculator.Add("4,6"));
    EXPECT_EQ(1, calculator.Add("1,0"));
}

// TDD Step 4: Unknown amount of numbers
TEST_F(StringCalculatorTest, UnknownAmountOfNumbers) {
    EXPECT_EQ(6, calculator.Add("1,2,3"));
    EXPECT_EQ(15, calculator.Add("1,2,3,4,5"));
    EXPECT_EQ(21, calculator.Add("1,2,3,4,5,6"));
}

// TDD Step 5: Handle newlines between numbers
TEST_F(StringCalculatorTest, NewlineDelimiters) {
    EXPECT_EQ(6, calculator.Add("1\n2,3"));
    EXPECT_EQ(6, calculator.Add("1,2\n3"));
    EXPECT_EQ(10, calculator.Add("1\n2\n3\n4"));
}

// TDD Step 6: Support different delimiters
TEST_F(StringCalculatorTest, CustomDelimiters) {
    EXPECT_EQ(3, calculator.Add("//;\n1;2"));
    EXPECT_EQ(6, calculator.Add("//|\n1|2|3"));
    EXPECT_EQ(10, calculator.Add("//:\n1:2:3:4"));
}

// TDD Step 7: Negative numbers throw exception
TEST_F(StringCalculatorTest, NegativeNumberThrowsException) {
    EXPECT_THROW(calculator.Add("1,-2,3"), NegativeNumberException);
}

TEST_F(StringCalculatorTest, SingleNegativeNumberShowsInMessage) {
    try {
        calculator.Add("1,-2,3");
        FAIL() << "Expected NegativeNumberException";
    } catch (const NegativeNumberException& e) {
        EXPECT_STREQ("negatives not allowed: -2", e.what());
    }
}

TEST_F(StringCalculatorTest, MultipleNegativeNumbersShowAllInMessage) {
    try {
        calculator.Add("1,-2,-3,4");
        FAIL() << "Expected NegativeNumberException";
    } catch (const NegativeNumberException& e) {
        EXPECT_STREQ("negatives not allowed: -2, -3", e.what());
    }
}

// TDD Step 8: Numbers bigger than 1000 ignored
TEST_F(StringCalculatorTest, NumbersBiggerThanThousandIgnored) {
    EXPECT_EQ(2, calculator.Add("2,1001"));
    EXPECT_EQ(1000, calculator.Add("1000,1001"));
    EXPECT_EQ(1003, calculator.Add("1,2,1000,2000"));
}

// TDD Step 9: Delimiters of any length
TEST_F(StringCalculatorTest, DelimitersOfAnyLength) {
    EXPECT_EQ(6, calculator.Add("//[***]\n1***2***3"));
    EXPECT_EQ(6, calculator.Add("//[||]\n1||2||3"));
    EXPECT_EQ(15, calculator.Add("//[abc]\n1abc2abc3abc4abc5"));
}

// Additional comprehensive tests for 100% coverage
TEST_F(StringCalculatorTest, EdgeCasesForFullCoverage) {
    EXPECT_EQ(999, calculator.Add("999"));
    EXPECT_EQ(3, calculator.Add("1,abc,2"));
    EXPECT_EQ(0, calculator.Add("//;\n"));
    EXPECT_EQ(0, calculator.Add("abc,def,ghi"));
}

TEST_F(StringCalculatorTest, BoundaryValueTesting) {
    EXPECT_EQ(1000, calculator.Add("1000"));
    EXPECT_EQ(0, calculator.Add("1001"));
    EXPECT_EQ(1001, calculator.Add("1,1000"));
}

TEST_F(StringCalculatorTest, ComplexDelimiterScenarios) {
    EXPECT_EQ(6, calculator.Add("//[##]\n1##2##3"));
    EXPECT_EQ(10, calculator.Add("//[%]\n1%2%3%4"));
    EXPECT_EQ(0, calculator.Add("//[***]\n"));
}

TEST_F(StringCalculatorTest, MixedValidAndInvalidNumbers) {
    EXPECT_EQ(6, calculator.Add("1,2,3,abc"));
    EXPECT_EQ(3, calculator.Add("1,,2"));
    EXPECT_EQ(6, calculator.Add("1,2,3,"));
}

TEST_F(StringCalculatorTest, CustomDelimiterWithSpecialCharacters) {
    EXPECT_EQ(6, calculator.Add("//[***]\n1***2***3"));
    EXPECT_EQ(6, calculator.Add("//[+++]\n1+++2+++3"));
    EXPECT_EQ(6, calculator.Add("//[...]\n1...2...3"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
