#ifndef SRC_SOURCE_CALCULATOR_H_
#define SRC_SOURCE_CALCULATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define INCORRECT_EXPRESSION 1
#define CALCULATION_ERROR 1


typedef struct stack {
    double operand;
    struct stack* down;
} Stack;


void push(Stack** top, double operat);
double pop(Stack** top);
int is_empty(Stack* top);

int is_function(char op);
int is_operator(char symbol);
int to_postfix(char* str, char* result);
int get_result(char* str, double* result, double x);

int compute(const char* str, char* str_result, double x);

#ifdef __cplusplus
}
#endif
#endif  //  SRC_SOURCE_CALCULATOR_H_
