#include "smartCalcModel.h"

#include <iostream>

bool SmartCalcModel::to_postfix() {
    bool error = count_bracket() || replace();
    std::stack<char> st;
    size_t k = 0, len_str = expression_.size();

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

    std::cout << "str = " << ex_postfix_ << "\nerror = " << error;
    return error;
}

int SmartCalcModel::evaluate(char* str, double* result, double x) {

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

int SmartCalcModel::is_func(char op) {
    int is_func = 0;
    if (op == 'c' || op == 's' || op == 't' ||
        op == 'C' || op == 'S' || op == 'T' ||
        op == 'q' || op == 'l' || op == 'L') {
        is_func = 1;
    }
    return is_func;
}

int SmartCalcModel::is_operator(char symbol) {
    int is_op = 0;
    if (symbol == '+' || symbol == '-' || symbol == '*' ||
        symbol == '/' || symbol == '^' || symbol == '%' ||
        symbol == '@' || symbol == '~') {
        is_op = 1;
    }
    return is_op;
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
    for (int i = 0; i < expression_.size(); i++) {
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

void SmartCalcModel::calculate(char op, double a, double b, double* result) {}

int main () {
    SmartCalcModel model;
    model.set_expression("sin( + cos(2 + 3)*atan(65/2))");
    model.to_postfix();

    return 0;
}