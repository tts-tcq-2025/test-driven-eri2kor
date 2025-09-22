#include <gtest/gtest.h>
#include "StringCalculator.h"

class StringCalculatorTest : public ::testing::Test {
protected:
    StringCalculator calculator;
};

// Step 1: Smallest failing test
TEST_F(StringCalculatorTest, EmptyStringReturnsZero) {
    EXPECT_EQ(0, calculator.Add(""));
}

TEST_F(StringCalculatorTest, SingleNumberReturnsThatNumber) {
    EXPECT_EQ(1, calculator.Add("1"));
    EXPECT_EQ(5, calculator.Add("5"));
}

TEST_F(StringCalculatorTest, TwoNumbersReturnSum) {
    EXPECT_EQ(3, calculator.Add("1,2"));
    EXPECT_EQ(10, calculator.Add("4,6"));
}

TEST_F(StringCalculatorTest, UnknownAmountOfNumbers) {
    EXPECT_EQ(6, calculator.Add("1,2,3"));
    EXPECT_EQ(15, calculator.Add("1,2,3,4,5"));
}

TEST_F(StringCalculatorTest, NewLineDelimiter) {
    EXPECT_EQ(6, calculator.Add("1\n2,3"));
    EXPECT_EQ(6, calculator.Add("1,2\n3"));
}

TEST_F(StringCalculatorTest, CustomDelimiter) {
    EXPECT_EQ(3, calculator.Add("//;\n1;2"));
    EXPECT_EQ(6, calculator.Add("//|\n1|2|3"));
}

TEST_F(StringCalculatorTest, NegativeNumbersThrowException) {
    EXPECT_THROW({
        calculator.Add("1,-2,3");
    }, NegativeNumberException);
    
    try {
        calculator.Add("1,-2,-3");
    } catch (const NegativeNumberException& e) {
        EXPECT_STREQ("negatives not allowed: -2, -3", e.what());
    }
}

TEST_F(StringCalculatorTest, NumbersBiggerThanThousandIgnored) {
    EXPECT_EQ(2, calculator.Add("2,1001"));
    EXPECT_EQ(1000, calculator.Add("1000,1001"));
}

TEST_F(StringCalculatorTest, CustomDelimiterAnyLength) {
    EXPECT_EQ(6, calculator.Add("//[***]\n1***2***3"));
    EXPECT_EQ(6, calculator.Add("//[||]\n1||2||3"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
