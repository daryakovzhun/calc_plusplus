#ifndef SMARTCALCCONTROLLER_H
#define SMARTCALCCONTROLLER_H

#include "smartCalcModel.h"

class SmartCalcController 
{
    private:
        SmartCalcModel *model;
    public:
        SmartCalcController(SmartCalcModel *m) : model(m) {};
        void set_expression(std::string expression);
        void set_x(double x);
        double get_result();
        void reset();
};

#endif
