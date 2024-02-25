#include <gtest/gtest.h>

#include "../include/Model.h"

class ModelCalcTest : public ::testing::Test {
 protected:
  s21::MathModel calculator_test;
};

TEST_F(ModelCalcTest, SimpleCalc1) {
  calculator_test.SetString("5+3+2+5+5+1+2+3+4+5+6+7+8+9");
  calculator_test.SetX("0");
  ASSERT_DOUBLE_EQ(std::stod(calculator_test.GetResult()), 65);
}

TEST_F(ModelCalcTest, SimpleCalc2) {
  calculator_test.SetString("5-3-2-5-5-1-2-3-4-5-6-7-8-9");
  calculator_test.SetX("0");
  ASSERT_DOUBLE_EQ(std::stod(calculator_test.GetResult()), -55);
}

TEST_F(ModelCalcTest, SimpleCalc3) {
  calculator_test.SetString("5143*1213*24532/1213/1445");
  calculator_test.SetX("0");
  ASSERT_NEAR(std::stod(calculator_test.GetResult()), 87313.5474048, 1e-7);
}

TEST_F(ModelCalcTest, SimpleCalc4) {
  calculator_test.SetString(
      "1.23456789+2.34567890-3.45678901*4.56789012/5.67890123");
  calculator_test.SetX("0");
  ASSERT_NEAR(std::stod(calculator_test.GetResult()), 0.79973842646, 1e-7);
}

TEST_F(ModelCalcTest, SimpleCalc5) {
  calculator_test.SetString("5");
  calculator_test.SetX("0");
  ASSERT_DOUBLE_EQ(std::stod(calculator_test.GetResult()), 5);
}

TEST_F(ModelCalcTest, SimpleCalc6) {
  calculator_test.SetString("2^3^2");
  calculator_test.SetX("0");
  ASSERT_DOUBLE_EQ(std::stod(calculator_test.GetResult()), 512);
}

TEST_F(ModelCalcTest, SimpleCalc7) {
  calculator_test.SetString("5*x");
  calculator_test.SetX("6");
  ASSERT_DOUBLE_EQ(std::stod(calculator_test.GetResult()), 30);
}

TEST_F(ModelCalcTest, SimpleCalc8) {
  calculator_test.SetString("2+x/x-x*(x%x)");
  calculator_test.SetX("3");
  ASSERT_DOUBLE_EQ(std::stod(calculator_test.GetResult()), 3);
}

TEST_F(ModelCalcTest, HardCalc1) {
  calculator_test.SetString(
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))"); 
  calculator_test.SetX("3");
  ASSERT_NEAR(std::stod(calculator_test.GetResult()), -30.0721649, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc2) {
  calculator_test.SetString("cos(2-sin(3+0.26*7+1))");
  calculator_test.SetX("3");
  ASSERT_NEAR(std::stod(calculator_test.GetResult()), -0.7681865, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc3) {
  calculator_test.SetString("10*(-5+log(2+(9/3)))");
  calculator_test.SetX("3");
  ASSERT_NEAR(std::stod(calculator_test.GetResult()), -43.0102999, 1e-6);
}

TEST_F(ModelCalcTest, HardCalc4) {
  calculator_test.SetString("asin(0.8)+63/(log(8)%7)");
  calculator_test.SetX("3");
  ASSERT_NEAR(std::stod(calculator_test.GetResult()), 70.687785, 1e-6);
}

TEST_F(ModelCalcTest, HardCalc5) {
  calculator_test.SetString(
      "acos((0+1))+asin(sqrt(81)-8.321)-atan(123%(5-2)+0.123)");
  calculator_test.SetX("3");
  ASSERT_NEAR(std::stod(calculator_test.GetResult()), 0.624014352, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc6) {
  calculator_test.SetString("sin(sin(sin(sin(sin(90)))))");
  calculator_test.SetX("3");
  ASSERT_NEAR(std::stod(calculator_test.GetResult()), 0.6023926, 1e-7);
}

TEST_F(ModelCalcTest, ErrorCalc1) {
  calculator_test.SetString("");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc2) {
  calculator_test.SetString("5+(3");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc3) {
  calculator_test.SetString("5)+3");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc4) {
  calculator_test.SetString("01%");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc5) {
  calculator_test.SetString("1+(2)2");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc6) {
  calculator_test.SetString("1+(+-2)");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc7) {
  calculator_test.SetString("*");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc8) {
  calculator_test.SetString("(^)");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc9) {
  calculator_test.SetString(")2+3(");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc10) {
  calculator_test.SetString("2..3");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc11) {
  calculator_test.SetString("7.1*2.3.2");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc12) {
  calculator_test.SetString("5+.2");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc13) {
  calculator_test.SetString("asin()");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc14) {
  calculator_test.SetString("%3");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc15) {
  calculator_test.SetString("0x00.2");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc16) {
  calculator_test.SetString("cos(*tan(2))");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc17) {
  calculator_test.SetString("5x");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc18) {
  calculator_test.SetString("xxxx");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc19) {
  calculator_test.SetString("xsin(3)");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

TEST_F(ModelCalcTest, ErrorCalc20) {
  calculator_test.SetString("x.");
  calculator_test.SetX("3");
  ASSERT_EQ(calculator_test.GetResult(), "ERROR");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
