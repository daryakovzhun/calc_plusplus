#ifndef SMARTCALCMODEL_H
#define SMARTCALCMODEL_H

#include <string>
#include <cctype>
#include <stack>

class SmartCalcModel
{
    public:
        SmartCalcModel() : result_(0), expression_(""), ex_postfix_("") {};
        void set_expression(std::string str) { expression_ = str; }
        void reset() {result_ = 0; expression_ = "";}
        double get_result();

        bool to_postfix();

    private:
        std::string expression_;
        std::string ex_postfix_;
        double result_;

        // bool to_postfix();
        int evaluate(char* str, double* result, double x);

        int get_priority(char op);
        bool count_bracket();
        int is_func(char op);
        int is_operator(char symbol);
        void replace_str (size_t* pos, std::string src, std::string dst);
        bool replace();
        void calculate(char op, double a, double b, double* result);
};

#endif