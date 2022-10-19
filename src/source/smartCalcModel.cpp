#include "smartCalcModel.h"

#include <QDebug>

bool SmartCalcModel::to_postfix() {
    if (expression_.empty() || (!std::isalpha(expression_[0]) && !std::isdigit(expression_[0]))) {
        return true;
    }
    if (ex_postfix_ != "") { return false; }

    bool error = count_bracket() || replace();
    std::stack<char> st;
    size_t len_str = expression_.size();

    for (size_t i = 0; i < len_str && !error; i++) {
        if (isdigit(expression_[i]) || expression_[i] == 'x' || expression_[i] == '.') {
            ex_postfix_ += expression_[i];
            if (i == len_str - 1 || (!isdigit(expression_[i + 1]) && expression_[i + 1] != '.'))
                ex_postfix_ += ' ';
        } else if (expression_[i] == '(' || is_func(expression_[i])) {
            st.push(expression_[i]);
        } else if (is_operator(expression_[i])) {
            char op = expression_[i], op2;
            while (!st.empty() && (op2 = st.top())) {
                st.pop();
                if (get_priority(op2) >= get_priority(op)) {
                    ex_postfix_ += op2; ex_postfix_ += ' ';
                } else {
                    st.push(op2);
                    break;
                }
            }
            st.push(op);
        } else if (expression_[i] == ')') {
            char top;
            if (expression_[i - 1] == '(') {
                error = true;
                break;
            }
            while (!st.empty() && (top = st.top()) != '(') {
                st.pop();
                ex_postfix_ += top; ex_postfix_ += ' ';
            }
            st.pop();
            if (!st.empty()) {
                top = st.top();
                if (is_func(top)) {
                    st.pop();
                    ex_postfix_ += top; ex_postfix_ += ' ';
                }
            }
        } else if (std::isalpha(expression_[i])) {
            error = true;
        }
    }

    while (!st.empty() && !error) {
        char op = st.top();
        st.pop();
        if ((op == '(' || op == ')')) {
            error = true;
            break;
        }
        ex_postfix_ += op; ex_postfix_ += ' ';
    }

    return error;
}

bool SmartCalcModel::check_double_dot (std::string* str_number) {
    const auto count_dot = std::count(str_number->cbegin(), str_number->cend(), '.');
    return count_dot > 1;
}

bool SmartCalcModel::evaluate() {
    setlocale(LC_NUMERIC, "C");
    std::stack<double> st;
    size_t len_str = ex_postfix_.size();
    bool error = false;
    for (size_t i = 0; i < len_str && !error; i++) {
        if (ex_postfix_[i] == 'x') {
            st.push(x_);
        } else if (isdigit(ex_postfix_[i]) || ex_postfix_[i] == '.') {
            std::string str_number;
            str_number += ex_postfix_[i];
            while (i != len_str - 1 &&  ex_postfix_[i + 1] != ' ') {
                str_number += ex_postfix_[i + 1];
                i++;
            }
            if (check_double_dot(&str_number)) { error = true; }
            st.push(atof(str_number.c_str()));
        } else if (is_func(ex_postfix_[i]) || is_operator(ex_postfix_[i])) {
            if (st.empty()) {
               error = true;
            } else {
                double a = st.top(), b = 0, res = 0;
                st.pop();
                if (ex_postfix_[i] == '@' || ex_postfix_[i] == '~' || is_func(ex_postfix_[i])) {
                    calculate(ex_postfix_[i], &a, 0, &res);
                } else {
                    if (st.empty()) {
                        error = true;
                    } else {
                        b = st.top();
                        st.pop();
                        calculate(ex_postfix_[i], &b, &a, &res);
                    }
                }
                if (std::isnan(res) || !std::isfinite(res)) {
                    error = true;
                }
                st.push(res);
            }
        }
    }

    if (error == false) {
        result_ = st.top();
        st.pop();
    }

    return error;
}

int SmartCalcModel::get_priority(char op) {
    int priority = -2;
    if (op == '+' || op == '-') {
        priority = 0;
    } else if (op == '*' || op == '/' || op == '%') {
        priority = 1;
    } else if (op == '^') {
        priority = 3;
    } else if (op == '~' || op == '@') {
        priority = 2;
    } else if (op == '(') {
        priority = -1;
    }
    return priority;
}

bool SmartCalcModel::count_bracket() {
    int count_op = 0, count_cl = 0;
    for (size_t i = 0; i < expression_.size(); i++) {
        if (expression_[i] == '(')
            count_op++;
        if (expression_[i] == ')')
            count_cl++;
    }
    return count_cl != count_op;
}

bool SmartCalcModel::is_func(char op) {
    std::string str_all_op = "cstCSTqlL";
    return std::count(str_all_op.cbegin(), str_all_op.cend(), op);
}

bool SmartCalcModel::is_operator(char symbol) {
    std::string str_all_op = "+-*/^%@~";
    return std::count(str_all_op.cbegin(), str_all_op.cend(), symbol);
}

void SmartCalcModel::replace_str (std::string src, std::string dst) {
    size_t pos = expression_.find(src);
    while(pos != std::string::npos) {
        expression_.replace(pos, src.size(), dst);
        pos = expression_.find(src, pos);
    }
}

bool SmartCalcModel::replace() {
    replace_str("acos(", "C(");
    replace_str("asin(", "S(");
    replace_str("atan(", "T(");
    replace_str("cos(", "c(");
    replace_str("sin(", "s(");
    replace_str("tan(", "t(");
    replace_str("sqrt(", "q(");
    replace_str("ln(", "l(");
    replace_str("log(", "L(");
    replace_str("mod", "%");

    if (expression_[0] == '+') { expression_[0] = '@'; }
    replace_str("(+", "(@");

    if (expression_[0] == '-') { expression_[0] = '~'; }
    replace_str("(-", "(~");

    size_t count_alfha = 0;
    bool error = false;
    for (size_t i = 0; i < expression_.size(); i++) {
        if (isalpha(expression_[i])) {
            count_alfha++;
            if (count_alfha > 1) {
                error = true;
                break;
            }
        } else {
            count_alfha = 0;
        }
    }

    return error;
}

void SmartCalcModel::calculate(char op, double* a, double* b, double* result) {
    if (op == '+') {
        *result = *a + *b;
    } else if (op == '-') {
        *result = *a - *b;
    } else if (op == '*') {
        *result = *a * *b;
    } else if (op == '/') {
        *result = *a / *b;
    } else if (op == '^') {
        *result = pow(*a, *b);
    } else if (op == '%') {
        *result = fmod(*a, *b);
    } else if (op == '@') {
        *result = *a;
    } else if (op == '~') {
        *result = -(*a);
    } else if (op == 'c') {
        *result = cos(*a);
    } else if (op == 's') {
        *result = sin(*a);
    } else if (op == 't') {
        *result = tan(*a);
    } else if (op == 'C') {
        *result = acos(*a);
    } else if (op == 'S') {
        *result = asin(*a);
    } else if (op == 'T') {
        *result = atan(*a);
    } else if (op == 'q') {
        *result = sqrt(*a);
    } else if (op == 'l') {
        *result = (double) logl(*a);
    } else if (op == 'L') {
        *result = (double) log10l(*a);
    }
}

