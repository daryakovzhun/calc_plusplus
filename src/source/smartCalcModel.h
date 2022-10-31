#ifndef SMARTCALCMODEL_H
#define SMARTCALCMODEL_H

#include <algorithm>
#include <cctype>
#include <clocale>
#include <cmath>
#include <stack>
#include <stdexcept>
#include <string>

class SmartCalcModel {
public:
  SmartCalcModel() : expression_(""), ex_postfix_(""), result_(0), x_(0){};
  void set_expression(std::string str) { expression_ = str; }
  void set_x(double x) { x_ = x; }
  void reset() {
    result_ = 0;
    x_ = 0;
    expression_ = "";
    ex_postfix_ = "";
  }
  double get_result() {
    bool error = to_postfix() || evaluate();
    if (error) {
      throw std::invalid_argument("Incorrect expression");
    }

    return result_;
  }

private:
  std::string expression_;
  std::string ex_postfix_;
  double result_, x_;

  bool to_postfix();
  bool evaluate();

  int get_priority(char op);
  bool count_bracket();
  bool is_func(char op);
  bool is_operator(char symbol);
  void replace_str(std::string src, std::string dst);
  bool replace();
  void calculate(char op, double *a, double *b, double *result);
  bool check_double_dot(std::string *str_number);
};

#endif
