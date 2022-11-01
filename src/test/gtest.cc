#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../source/smartCalcModel.h"

using namespace s21;

TEST(SmartCalc, asin) {
  SmartCalcModel model;

  double x = -0.26546;
  double test_result = asin(x);
  model.set_expression("asin(x)");
  model.set_x(x);
  double my_result = model.get_result();
  model.reset();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, acos) {
  SmartCalcModel model;

  double x = -0.26546;
  double test_result = acos(x);
  model.set_expression("acos(x)");
  model.set_x(x);
  double my_result = model.get_result();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, atan) {
  SmartCalcModel model;

  double x = 10000;
  double test_result = atan(x);
  model.set_expression("atan(x)");
  model.set_x(x);
  double my_result = model.get_result();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, log) {
  SmartCalcModel model;

  double x = 0.1;
  double test_result = log10l(x);
  model.set_expression("log(x)");
  model.set_x(x);
  double my_result = model.get_result();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, sin) {
  SmartCalcModel model;

  double x = -1000;
  double test_result = sin(x);
  model.set_expression("sin(x)");
  model.set_x(x);
  double my_result = model.get_result();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, cos) {
  SmartCalcModel model;

  double x = 102654;
  double test_result = cos(x);
  model.set_expression("cos(x)");
  model.set_x(x);
  double my_result = model.get_result();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, tan) {
  SmartCalcModel model;

  double x = -1.9999;
  double test_result = tan(x);
  model.set_expression("tan(x)");
  model.set_x(x);
  double my_result = model.get_result();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, ln) {
  SmartCalcModel model;

  double x = 0.1;
  double test_result = logl(x);
  model.set_expression("ln(x)");
  model.set_x(x);
  double my_result = model.get_result();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}
TEST(SmartCalc, sqrt) {
  SmartCalcModel model;

  double x = 25468;
  double test_result = sqrt(x);
  model.set_expression("sqrt(x)");
  model.set_x(x);
  double my_result = model.get_result();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}
TEST(SmartCalc, pow) {
  SmartCalcModel model;

  double x = 6;
  double test_result = 1 + pow(2, x);
  model.set_expression("1 + 2^(x)");
  model.set_x(x);
  double my_result = model.get_result();

  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, arifmetic_test) {
  SmartCalcModel model;
  model.set_expression("-1 + 2 - 4 * (+10 / 2 + 5 mod 2)");
  double my_result = model.get_result();

  EXPECT_EQ(fabs(my_result - (-23.0)) < 1e-6, 1);
}

TEST(SmartCalc, incorrect_test) {
  SmartCalcModel model;
  model.set_expression("2^(3)) + 4");
  EXPECT_ANY_THROW(model.get_result());
}

TEST(SmartCalc, incorrect_input_1) {
  SmartCalcModel model;
  model.set_expression("san(5)");
  EXPECT_ANY_THROW(model.get_result());
}

TEST(SmartCalc, incorrect_input_2) {
  SmartCalcModel model;
  model.set_expression("f");
  EXPECT_ANY_THROW(model.get_result());
}

TEST(SmartCalc, incorrect_input_3) {
  SmartCalcModel model;
  model.set_expression("");
  EXPECT_ANY_THROW(model.get_result());
}

TEST(SmartCalc, incorrect_input_4) {
  SmartCalcModel model;
  model.set_expression("()");
  EXPECT_ANY_THROW(model.get_result());
}

TEST(SmartCalc, incorrect_input_5) {
  SmartCalcModel model;
  model.set_expression("1+");
  EXPECT_ANY_THROW(model.get_result());
}

TEST(SmartCalc, incorrect_input_6) {
  SmartCalcModel model;
  model.set_expression("1/0");
  EXPECT_ANY_THROW(model.get_result());
}

TEST(SmartCalc, incorrect_input_7) {
  SmartCalcModel model;
  model.set_expression("+");
  EXPECT_ANY_THROW(model.get_result());
}

TEST(SmartCalc, incorrect_input_8) {
  SmartCalcModel model;
  model.set_expression("((2+3)");
  EXPECT_ANY_THROW(model.get_result());
}

TEST(SmartCalc, incorrect_input_9) {
  SmartCalcModel model;
  model.set_expression("5..6");
  EXPECT_ANY_THROW(model.get_result());
}

TEST(SmartCalc, repeat_input_1) {
  SmartCalcModel model;
  model.set_expression("2+3");
  double result = model.get_result();
  result = model.get_result();
  EXPECT_EQ(fabs(result - 5.0) < 1e-6, 1);
}

TEST(SmartCalc, exp_negative) {
  SmartCalcModel model;
  model.set_expression("2e-3");
  double my_result = model.get_result();
  double test_result = 0.002;
  EXPECT_EQ(fabs(my_result - test_result) < 1e-6, 1);
}

TEST(SmartCalc, unar_and_op) {
  SmartCalcModel model;
  model.set_expression("3/-3 - 6/-2");
  double my_result = model.get_result();
  EXPECT_EQ(fabs(my_result - 2.0) < 1e-6, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}