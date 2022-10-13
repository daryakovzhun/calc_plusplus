#include "calculator.h"

#include "QDebug"

using namespace std;

void replace_str(char* str) {
    char temp[226];
    int k = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == 'c' && str[i + 1] == 'o') {
            temp[k++] = 'c';
            i += 2;
        } else if (str[i] == 's' && str[i + 1] == 'i') {
            temp[k++] = 's';
            i += 2;
        } else if (str[i] == 't' && str[i + 1] == 'a') {
            temp[k++] = 't';
            i += 2;
        } else if (str[i] == 'a' && str[i + 1] == 'c') {
            temp[k++] = 'a';
            i += 3;
        } else if (str[i] == 'a' && str[i + 1] == 's') {
            temp[k++] = 'b';
            i += 3;
        } else if (str[i] == 'a' && str[i + 1] == 't') {
            temp[k++] = 'd';
            i += 3;
        } else if (str[i] == 's' && str[i + 1] == 'q') {
            temp[k++] = 'q';
            i += 3;
        } else if (str[i] == 'l' && str[i + 1] == 'n') {
            temp[k++] = 'l';
            i += 2;
        } else if (str[i] == 'l' && str[i + 1] == 'o') {
            temp[k++] = 'g';
            i += 2;
        } else if (str[i] == 'm' && str[i + 1] == 'o') {
            temp[k++] = '%';
            i += 2;
        } else if (str[i] == '+' && (i == 0 || str[i - 1] == '(' || is_operator(str[i - 1]))) {
            temp[k++] = '@';
        } else if (str[i] == '-' && (i == 0 || str[i - 1] == '(' || is_operator(str[i - 1]))) {
            temp[k++] = '~';
        } else {
            temp[k++] = str[i];
        }
    }
    temp[k++] = '\0';
    snprintf(str, sizeof(temp), "%s", temp);
    // strcpy(str, temp);
}

int is_func(char op) {
    int is_func = 0;
    if (op == 'c' || op == 's' || op == 't' ||
        op == 'a' || op == 'b' || op == 'd' ||
        op == 'q' || op == 'l' || op == 'g') {
        is_func = 1;
    }
    return is_func;
}

int is_operator(char symbol) {
    int is_op = 0;
    if (symbol == '+' || symbol == '-' || symbol == '*' ||
        symbol == '/' || symbol == '^' || symbol == '%' ||
        symbol == '@' || symbol == '~') {
        is_op = 1;
    }
    return is_op;
}

int get_priority(char op) {
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

int count_bracket(char* str) {
    int count_op = 0, count_cl = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '(')
            count_op++;
        if (str[i] == ')')
            count_cl++;
    }
    return count_cl != count_op;
}

int to_postfix(char* str, char* result) {
    int error = 0;
    error = count_bracket(str);
    replace_str(str);
    stack<char> st;
    size_t k = 0, len_str = strlen(str);

    for (size_t i = 0; i < len_str && error == 0; i++) {
        if (isdigit(str[i]) || str[i] == 'x'  || str[i] == '.') {
            result[k++] = str[i];
            if (i == len_str - 1 || (!isdigit(str[i + 1]) && str[i + 1] != '.'))
                result[k++] = ' ';
        } else if (str[i] == '(' || is_func(str[i])) {
            st.push(str[i]);
        } else if (is_operator(str[i])) {
            char op = str[i], op2;
            while (!st.empty() && (op2 = st.top())) {
                st.pop();
                if (get_priority(op2) >= get_priority(op)) {
                    result[k++] = op2;
                    result[k++] = ' ';
                } else {
                    st.push(op2);
                    break;
                }
            }
            st.push(op);
        } else if (str[i] == ')') {
            char top;
            if (str[i - 1] == '(') {
                error = INCORRECT_EXPRESSION;
                break;
            }
            while (!st.empty() && (top = st.top()) != '(') {
                st.pop();
                result[k++] = top;
                result[k++] = ' ';
            }
            st.pop();
            if (!st.empty()) {
                top = st.top();
                st.pop();
                if (is_func(top)) {
                    result[k++] = top;
                    result[k++] = ' ';
                } else {
                    st.push(top);
                }
            }
        }
    }

    while (!st.empty() && !error) {
        char op =  st.top();
        st.pop();
        if ((op == '(' || op == ')')) {
            error = INCORRECT_EXPRESSION;
        }
        result[k++] = op;
        result[k++] = ' ';
    }
    result[k] = '\0';

    return error;
}
