#include "calculator.h"

#include <iostream>
#include <QDebug>

int compute(const char* str_const, char* str_result, double x) {
    char str[226];
    snprintf(str, sizeof(str), "%s", str_const);
    char reverse_order[1000];
    int error = 0;

    if ((error = to_postfix(str, reverse_order)) == INCORRECT_EXPRESSION) {
        char incorrect[25] = "Incorrect expression";
        snprintf(str_result, sizeof(incorrect), "%s", incorrect);
    } else {
        double result;
        if ((error = get_result(reverse_order, &result, x)) == CALCULATION_ERROR) {
            char error[10] = "Error";
            snprintf(str_result, sizeof(error), "%s", error);
        } else {
            snprintf(str_result, sizeof(str), "%0.7lf", result);
        }
    }

    return error;
}
