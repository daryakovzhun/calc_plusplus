#ifndef SMARTCALCCONTROLLER_H
#define SMARTCALCCONTROLLER_H

#include "smartCalcModel.h"

class SmartCalcController 
{
    private:
        SmartCalcModel *model;
    public:
        SmartCalcController(SmartCalcModel *m):model(m) {};
        double add(double a);
        double sub(double a);
        double mult(double a);
        double div(double a);
        void reset();
};

#endif