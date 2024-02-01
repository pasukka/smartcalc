#include <gtest/gtest.h>

#include "model.h"

#define EPSILON 1e-6

TEST(ParserTest, Error_1) {
  std::string str = "4*7*=";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_2) {
  std::string str = "sincos(5)=";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_3) {
  std::string str = "5+4*cos(5x))=";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_4) {
  std::string str = "5+4*cos((5x)";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_5) {
  std::string str = "sinb(8x)";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_6) {
  std::string str = ",";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_7) {
  std::string str = "sin(8x))";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_8) {
  std::string str = "ышт(0)";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_9) {
  std::string str = "sin()7";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_10) {
  std::string str = "7sin";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_11) {
  std::string str = "7sin()";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_12) {
  std::string str = "(()";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_13) {
  std::string str = "logs(8.1e+2)";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_14) {
  std::string str = "8.1e2";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_15) {
  std::string str = "acos(10)";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_16) {
  std::string str = "acos(x)";
  std::string x = "2";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_17) {
  std::string str = "10-*2";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::ERROR);
}

TEST(ParserTest, Error_18) {
  std::string str = "10/0";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::NaN);
}

TEST(ParserTest, Test_1) {
  std::string str = "sin(8)";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 0.98935824662, EPSILON);
}

TEST(ParserTest, Test_2) {
  std::string str = "10--2";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 12.0, EPSILON);
}

TEST(ParserTest, Test_3) {
  std::string str = "4+sqrt(4)-5";
  std::string x = "";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 1.0, EPSILON);
}

TEST(ParserTest, Test_4) {
  std::string str = "sin(x)";
  std::string x = "8";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 0.989358, EPSILON);
}

TEST(ParserTest, Test_5) {
  std::string str = "cos(3*x)";
  std::string x = "2";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 0.960170, EPSILON);
}

TEST(ParserTest, Test_6) {
  std::string str = "tan(x)";
  std::string x = "2";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), -2.185040, EPSILON);
}

TEST(ParserTest, Test_7) {
  std::string str = "atan(8/x)";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 1.107149, EPSILON);
}

TEST(ParserTest, Test_8) {
  std::string str = "5+4.5*8-9";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 32, EPSILON);
}

TEST(ParserTest, Test_9) {
  std::string str = "87.03e-3=";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 0.087030, EPSILON);
}

TEST(ParserTest, Test_10) {
  std::string str = "ln(8)";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 2.079441, EPSILON);
}

TEST(ParserTest, Test_11) {
  std::string str = "log(8.1e-2)";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), -1.091514, EPSILON);
}

TEST(ParserTest, Test_12) {
  std::string str = "log(8.1e+2)";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 2.908485, EPSILON);
}

TEST(ParserTest, Test_13) {
  std::string str = "asin(0.1)";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 0.100167, EPSILON);
}

TEST(ParserTest, Test_14) {
  Model m;
  std::string str = "sqrt";
  m.update_equation(str);
  str = "(2)";
  std::string x = "4";
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 1.414214, EPSILON);
}

TEST(ParserTest, Test_15) {
  std::string str = "2^10";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 1024, EPSILON);
}

TEST(ParserTest, Test_16) {
  std::string str = "2mod3";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 2, EPSILON);
}

TEST(ParserTest, Test_17) {
  std::string str = "acos(0.1)";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 1.470629, EPSILON);
}

TEST(ParserTest, Test_18) {
  std::string str = "-10-2";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), -12, EPSILON);
}

TEST(ParserTest, Test_19) {
  std::string str = "10-(-2)=";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 12, EPSILON);
}

TEST(ParserTest, Test_20) {
  std::string str = "10+(-2)=";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 8, EPSILON);
}

TEST(ParserTest, Test_21) {
  std::string str = "-10+2";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), -8, EPSILON);
}

TEST(ParserTest, Test_22) {
  std::string str = "+10";
  std::string x = "4";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 10, EPSILON);
}

TEST(ParserTest, Test_23) {
  std::string str = "5+4*cos(5x)";
  std::string x = "1.0";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 6.134649, EPSILON);
}

TEST(ParserTest, Test_24) {
  std::string str = "sin(56.03e-1)+5";
  std::string x = "1.0";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 4.371062, EPSILON);
}

TEST(ParserTest, Test_25) {
  std::string str = "2---4";
  std::string x = "1.0";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), -2.0, EPSILON);
}

TEST(ParserTest, Test_26) {
  std::string str = "2-(+(-4))";
  std::string x = "1.0";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), 6.0, EPSILON);
}

TEST(ParserTest, Test_27) {
  std::string str = "+-2";
  std::string x = "1.0";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), -2.0, EPSILON);
}

TEST(ParserTest, Test_28) {
  std::string str = "-+2";
  std::string x = "1.0";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), -2.0, EPSILON);
}

TEST(ParserTest, Test_29) {
  std::string str = "-asin(0.1)";
  std::string x = "1.0";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), -0.100167, EPSILON);
}

TEST(ParserTest, Test_30) {
  std::string str = "-10";
  std::string x = "1.0";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), -10.0, EPSILON);
}

TEST(ParserTest, Test_31) {
  std::string str = "-sin(x)";
  std::string x = "2.980000";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), -0.16089, EPSILON);
}

TEST(ParserTest, Test_32) {
  std::string str = "-sin(2.980000)";
  std::string x = "2.980000";
  Model m;
  m.set_x(x);
  m.update_equation(str);
  Error error = m.calculate();
  EXPECT_EQ(error, Error::OK);
  EXPECT_NEAR(m.get_answer(), -0.16089, EPSILON);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}