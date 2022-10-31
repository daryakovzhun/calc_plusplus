#include "smartCalcController.h"

namespace s21 {
void SmartCalcController::set_expression(std::string expression) {
  model->set_expression(expression);
}

void SmartCalcController::set_x(double x) { model->set_x(x); }

double SmartCalcController::get_result() { return model->get_result(); }

void SmartCalcController::reset() { model->reset(); }
}  // namespace s21