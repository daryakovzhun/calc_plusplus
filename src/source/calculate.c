#include "calculator.h"
#include <locale.h>

void calculate(char op, double a, double b, double* result) {
    if (op == '+') {
        *result = a + b;
    } else if (op == '-') {
        *result = a - b;
    } else if (op == '*') {
        *result = a * b;
    } else if (op == '/') {
        *result = a / b;
    } else if (op == '^') {
        *result = pow(a, b);
    } else if (op == '%') {
        *result = fmod(a, b);
    } else if (op == '@') {
        *result = a;
    } else if (op == '~') {
        *result = -a;
    } else if (op == 'c') {
        *result = cos(a);
    } else if (op == 's') {
        *result = sin(a);
    } else if (op == 't') {
        *result = tan(a);
    } else if (op == 'a') {
        *result = acos(a);
    } else if (op == 'b') {
        *result = asin(a);
    } else if (op == 'd') {
        *result = atan(a);
    } else if (op == 'q') {
        *result = sqrt(a);
    } else if (op == 'l') {
        *result = (double) logl(a);
    } else if (op == 'g') {
        *result = (double) log10l(a);
    }
}

int get_result(char* str, double* result, double x) {
    setlocale(LC_NUMERIC, "C");
    Stack* st = NULL;
    int len_str = strlen(str), error = 0;
    for (int i = 0; i < len_str && !error; i++) {
        if (str[i] == 'x') {
            push(&st, x);
        } else if (isdigit(str[i]) || str[i] == '.') {
            char temp[50];
            int k = 0;
            temp[k++] = str[i];
            while (i != len_str - 1 &&  str[i + 1] != ' ') {
                temp[k++] = str[i + 1];
                i++;
            }
            temp[k++] = '\0';
            push(&st, atof(temp));
        } else if (is_function(str[i]) || is_operator(str[i])) {
            if (is_empty(st)) {
               error = INCORRECT_EXPRESSION;
            } else {
                double a = pop(&st), b = 0, res = 0;
                if (str[i] == '@' || str[i] == '~' || is_function(str[i])) {
                    calculate(str[i], a, 0, &res);
                } else {
                    if (is_empty(st)) {
                        error = INCORRECT_EXPRESSION;
                    } else {
                        b = pop(&st);
                        calculate(str[i], b, a, &res);
                    }
                }
                if (isnan(res) || !isfinite(res)) {
                    error = CALCULATION_ERROR;
                }
                push(&st, res);
            }
        }
    }

    if (error != CALCULATION_ERROR)
        *result = pop(&st);

    return error;
}

