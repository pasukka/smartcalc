#include <gtest/gtest.h>

#include "calculator.h"

TEST(LexemeTest, SimpleConstructorInt) {
  Lexeme<int> k;
  Lexeme l(5);
  Lexeme o("lol");
  Lexeme u("+");

  EXPECT_EQ(5, l.value);
  EXPECT_EQ("lol", o.value);
  EXPECT_EQ("+", u.value);
}

TEST(ParserTest, ParsingString) {
  std::string str = "2mod3+56x";
  std::string exp_str = "2mod3+56*x";
  std::string str2 = input(str);

  EXPECT_EQ(exp_str, str2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}