#include "calculator.h"

void push(Stack** top, double operat) {
    Stack* up = malloc(sizeof(Stack));
    if (up != NULL) {
        up->operand = operat;
        up->down = *top;
        *top = up;
    } else {
        printf("Error malloc");
    }
}

double pop(Stack** top) {
    Stack* temp = *top;
    double operator = (*top)->operand;
    *top = (*top)->down;
    free(temp);

    return operator;
}

int is_empty(Stack* top) {
    return top == NULL;
}
