#include "calculator.h"
#include <locale.h>

using namespace std;

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
    stack<double> st;
    int len_str = strlen(str), error = 0;
    for (int i = 0; i < len_str && !error; i++) {
        if (str[i] == 'x') {
            st.push(x);
        } else if (isdigit(str[i]) || str[i] == '.') {
            char temp[50];
            int k = 0;
            temp[k++] = str[i];
            while (i != len_str - 1 &&  str[i + 1] != ' ') {
                temp[k++] = str[i + 1];
                i++;
            }
            temp[k++] = '\0';
            st.push(atof(temp));
        } else if (is_func(str[i]) || is_operator(str[i])) {
            if (st.empty()) {
               error = INCORRECT_EXPRESSION;
            } else {
                double a = st.top(), b = 0, res = 0;
                st.pop();
                if (str[i] == '@' || str[i] == '~' || is_func(str[i])) {
                    calculate(str[i], a, 0, &res);
                } else {
                    if (st.empty()) {
                        error = INCORRECT_EXPRESSION;
                    } else {
                        b = st.top();
                        st.pop();
                        calculate(str[i], b, a, &res);
                    }
                }
                if (isnan(res) || !isfinite(res)) {
                    error = CALCULATION_ERROR;
                }
                st.push(res);
            }
        }
    }

    if (error != CALCULATION_ERROR) {
        *result = st.top();
        st.pop();
    }


    return error;
}

