#include <gtest/gtest.h>
#include "StringCalculator.h"

class StringCalculatorTest : public ::testing::Test {
protected:
    StringCalculator calculator;
};

TEST_F(StringCalculatorTest, EmptyStringReturnsZero) {
    EXPECT_EQ(0, calculator.Add(""));
}

TEST_F(StringCalculatorTest, SingleNumberReturnsThatNumber) {
    EXPECT_EQ(1, calculator.Add("1"));
    EXPECT_EQ(5, calculator.Add("5"));
    EXPECT_EQ(0, calculator.Add("0"));
}

TEST_F(StringCalculatorTest, TwoNumbersReturnSum) {
    EXPECT_EQ(3, calculator.Add("1,2"));
    EXPECT_EQ(10, calculator.Add("4,6"));
    EXPECT_EQ(1, calculator.Add("1,0"));
}

TEST_F(StringCalculatorTest, MultipleNumbersReturnSum) {
    EXPECT_EQ(6, calculator.Add("1,2,3"));
    EXPECT_EQ(15, calculator.Add("1,2,3,4,5"));
    EXPECT_EQ(21, calculator.Add("1,2,3,4,5,6"));
}

TEST_F(StringCalculatorTest, NewLineDelimiterWorks) {
    EXPECT_EQ(6, calculator.Add("1\n2,3"));
    EXPECT_EQ(6, calculator.Add("1,2\n3"));
    EXPECT_EQ(10, calculator.Add("1\n2\n3\n4"));
}

TEST_F(StringCalculatorTest, CustomSingleCharDelimiter) {
    EXPECT_EQ(3, calculator.Add("//;\n1;2"));
    EXPECT_EQ(6, calculator.Add("//|\n1|2|3"));
    EXPECT_EQ(10, calculator.Add("//:\n1:2:3:4"));
}

TEST_F(StringCalculatorTest, CustomMultiCharDelimiter) {
    EXPECT_EQ(6, calculator.Add("//[***]\n1***2***3"));
    EXPECT_EQ(6, calculator.Add("//[||]\n1||2||3"));
    EXPECT_EQ(10, calculator.Add("//[abc]\n1abc2abc3abc4"));
}

TEST_F(StringCalculatorTest, SingleNegativeNumberThrowsException) {
    try {
        calculator.Add("1,-2,3");
        FAIL() << "Expected NegativeNumberException";
    } catch (const NegativeNumberException& e) {
        EXPECT_STREQ("negatives not allowed: -2", e.what());
    }
}

TEST_F(StringCalculatorTest, MultipleNegativeNumbersThrowsException) {
    try {
        calculator.Add("1,-2,-3,4");
        FAIL() << "Expected NegativeNumberException";
    } catch (const NegativeNumberException& e) {
        EXPECT_STREQ("negatives not allowed: -2, -3", e.what());
    }
}

TEST_F(StringCalculatorTest, NumbersBiggerThanThousandIgnored) {
    EXPECT_EQ(2, calculator.Add("2,1001"));
    EXPECT_EQ(1000, calculator.Add("1000,1001"));
    EXPECT_EQ(1003, calculator.Add("1,2,1000,2000"));
}

TEST_F(StringCalculatorTest, BoundaryValues) {
    EXPECT_EQ(1000, calculator.Add("1000"));
    EXPECT_EQ(0, calculator.Add("1001"));
    EXPECT_EQ(999, calculator.Add("999"));
}

TEST_F(StringCalculatorTest, InvalidNumbersIgnored) {
    EXPECT_EQ(3, calculator.Add("1,abc,2"));
    EXPECT_EQ(0, calculator.Add("abc,def"));
    EXPECT_EQ(5, calculator.Add("2,xyz,3"));
}

TEST_F(StringCalculatorTest, ComplexScenarios) {
    EXPECT_EQ(6, calculator.Add("//[###]\n1###2###3"));
    EXPECT_EQ(10, calculator.Add("1\n2,3\n4"));
    EXPECT_EQ(0, calculator.Add("//;\n"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
