#include "smartCalcController.h"

double SmartCalcController::add(double a)
{
    model->add(a);
    return model->getData();
}

double SmartCalcController::sub(double a)
{
    model->add(-a);
    return model->getData();
}

double SmartCalcController::mult(double a)
{
    model->mult(a);
    return model->getData();
}

double SmartCalcController::div(double a)
{
    model->mult(1.0/a);
    return model->getData();
}

void SmartCalcController::reset(){
    model->reset();
}