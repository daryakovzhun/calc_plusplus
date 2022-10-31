#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../source/smartCalcModel.h"

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
  int error = 0;
  // try {
  //   double my_result = model.get_result();
  // } catch (const std::exception& e) {
  //   error = 1;
  // }
  EXPECT_ANY_THROW(model.get_result());

  // EXPECT_EQ(error, 1);
}

TEST(SmartCalc, incorrect_input_1) {
  SmartCalcModel model;
  model.set_expression("san(5)");
  int error = 0;
  try {
    double my_result = model.get_result();
  } catch (const std::exception& e) {
    error = 1;
  }

  EXPECT_EQ(error, 1);
}

TEST(SmartCalc, incorrect_input_2) {
  SmartCalcModel model;
  model.set_expression("f");
  int error = 0;
  try {
    double my_result = model.get_result();
  } catch (const std::exception& e) {
    error = 1;
  }

  EXPECT_EQ(error, 1);
}

TEST(SmartCalc, incorrect_input_3) {
  SmartCalcModel model;
  model.set_expression("");
  int error = 0;
  try {
    double my_result = model.get_result();
  } catch (const std::exception& e) {
    error = 1;
  }

  EXPECT_EQ(error, 1);
}

TEST(SmartCalc, incorrect_input_4) {
  SmartCalcModel model;
  model.set_expression("()");
  int error = 0;
  try {
    double my_result = model.get_result();
  } catch (const std::exception& e) {
    error = 1;
  }

  EXPECT_EQ(error, 1);
}

TEST(SmartCalc, incorrect_input_5) {
  SmartCalcModel model;
  model.set_expression("1+");
  int error = 0;
  try {
    double my_result = model.get_result();
  } catch (const std::exception& e) {
    error = 1;
  }

  EXPECT_EQ(error, 1);
}

TEST(SmartCalc, incorrect_input_6) {
  SmartCalcModel model;
  model.set_expression("1/0");
  int error = 0;
  try {
    double my_result = model.get_result();
  } catch (const std::exception& e) {
    error = 1;
  }

  EXPECT_EQ(error, 1);
}

TEST(SmartCalc, incorrect_input_7) {
  SmartCalcModel model;
  model.set_expression("+");
  int error = 0;
  try {
    double my_result = model.get_result();
  } catch (const std::exception& e) {
    error = 1;
  }

  EXPECT_EQ(error, 1);
}

TEST(SmartCalc, incorrect_input_8) {
  SmartCalcModel model;
  model.set_expression("((2+3)");
  int error = 0;
  try {
    double my_result = model.get_result();
  } catch (const std::exception& e) {
    error = 1;
  }

  EXPECT_EQ(error, 1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}