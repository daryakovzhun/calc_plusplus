#ifndef SMARTCALCCONTROLLER_H
#define SMARTCALCCONTROLLER_H

#include "smartCalcModel.h"

namespace s21 {
class SmartCalcController {
 private:
  SmartCalcModel *model;

 public:
  SmartCalcController(SmartCalcModel *m) : model(m){};
  void set_expression(std::string expression);
  void set_x(double x);
  double get_result();
  void reset();
};
}  // namespace s21

#endif
