#include <check.h>
#include "../source/calculator.h"

START_TEST(asin_test) {
    static double x = -1;
    double test_result = asin(x);
    char input[226] = "asin(", result[226], test[226], x_str[226];
    sprintf(x_str, "%0.7lf", x);
    strcat(input, x_str);
    strcat(input, ")");

    compute(input, result, 0);
    sprintf(test, "%0.7lf", test_result);

    ck_assert_str_eq(result, test);
    x += 0.0000001;
}
END_TEST

START_TEST(acos_test) {
    static double x = 1;
    double test_result = acos(x);
    char input[226] = "acos(", result[226], test[226], x_str[226];
    sprintf(x_str, "%0.7lf", x);
    strcat(input, x_str);
    strcat(input, ")");

    compute(input, result, 0);
    sprintf(test, "%0.7lf", test_result);

    ck_assert_str_eq(result, test);
    x -= 0.0000001;
}
END_TEST

START_TEST(atan_test) {
    static double x = 100000;
    double test_result = atan(x);
    char input[226] = "atan(", result[226], test[226], x_str[226];
    sprintf(x_str, "%0.7lf", x);
    strcat(input, x_str);
    strcat(input, ")");

    compute(input, result, 0);
    sprintf(test, "%0.7lf", test_result);

    ck_assert_str_eq(result, test);
    x += 100;
}
END_TEST

START_TEST(log_test) {
   
    static double x = 0.1;
    double test_result = log10l(x);
    char input[226] = "log(", result[226], test[226], x_str[226];
    sprintf(x_str, "%0.7lf", x);
    strcat(input, x_str);
    strcat(input, ")");

    compute(input, result, 0);
    sprintf(test, "%0.7lf", test_result);
    x += 10;
    ck_assert_str_eq(result, test);
    
}
END_TEST

START_TEST(sin_test) {
   
    static double x = -100000;
    double test_result = sin(x);
    char input[226] = "sin(", result[226], test[226], x_str[226];
    sprintf(x_str, "%0.7lf", x);
    strcat(input, x_str);
    strcat(input, ")");

    compute(input, result, 0);
    sprintf(test, "%0.7lf", test_result);
    x += 10000;
    ck_assert_str_eq(result, test);
    
}
END_TEST

START_TEST(cos_test) {
   
    static double x = -100000;
    double test_result = cos(x);
    char input[226] = "cos(", result[226], test[226], x_str[226];
    sprintf(x_str, "%0.7lf", x);
    strcat(input, x_str);
    strcat(input, ")");

    compute(input, result, 0);
    sprintf(test, "%0.7lf", test_result);
    x += 10000;
    ck_assert_str_eq(result, test);
    
}
END_TEST

START_TEST(tan_test) {
   
    static double x = -1.9999;
    double test_result = tan(x);
    char input[226] = "tan(", result[226], test[226], x_str[226];
    sprintf(x_str, "%0.7lf", x);
    strcat(input, x_str);
    strcat(input, ")");

    compute(input, result, 0);
    sprintf(test, "%0.7lf", test_result);
    x += 0.0001;
    ck_assert_str_eq(result, test);
    
}
END_TEST

START_TEST(ln_test) {
   
    static double x = 0.1;
    double test_result = logl(x);
    char input[226] = "ln(", result[226], test[226], x_str[226];
    sprintf(x_str, "%0.7lf", x);
    strcat(input, x_str);
    strcat(input, ")");

    compute(input, result, 0);
    sprintf(test, "%0.7lf", test_result);
    x += 10;
    ck_assert_str_eq(result, test);
    
}
END_TEST

START_TEST(sqrt_test) {
   
    static double x = 0;
    double test_result = sqrt(x);
    char input[226] = "sqrt(", result[226], test[226], x_str[226];
    sprintf(x_str, "%0.7lf", x);
    strcat(input, x_str);
    strcat(input, ")");

    compute(input, result, 0);
    sprintf(test, "%0.7lf", test_result);
    x += 10.01;
    ck_assert_str_eq(result, test);
    
}
END_TEST

START_TEST(pow_test) {
   
    static double x = -10;
    double test_result = pow(2, x);
    char input[226] = "2^(", result[226], test[226], x_str[226];
    sprintf(x_str, "%0.7lf", x);
    strcat(input, x_str);
    strcat(input, ")");

    compute(input, result, 0);
    sprintf(test, "%0.7lf", test_result);
    x += 0.01;
    ck_assert_str_eq(result, test);
    
}
END_TEST

START_TEST(arifmetic_test) {
    char input[226] = "-1 + 2 - 4 * (+10 / 2 + 5 mod 2)", result[226], test[226] = "-23.0000000";

    compute(input, result, 0);
    ck_assert_str_eq(result, test);
    
}
END_TEST

START_TEST(incorrect_test) {

    char input[226] = "2^(3)) + 4", result[226], test[226], x_str[226];
    ck_assert_int_eq(compute(input, result, 0), 1);
}
END_TEST

START_TEST(error_test) {

    char input[226] = "1 / 0", result[226], test[226], x_str[226];
    ck_assert_int_eq(compute(input, result, 0), 1);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Test_calculator");
    TCase *tc1 = tcase_create("Test_calculator");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1);
    tcase_add_loop_test(tc1, asin_test, 0, 1000);
    tcase_add_loop_test(tc1, acos_test, 0, 1000);
    tcase_add_loop_test(tc1, atan_test, 0, 1000);
    tcase_add_loop_test(tc1, log_test, 0, 1000);
    tcase_add_loop_test(tc1, sin_test, 0, 1000);
    tcase_add_loop_test(tc1, cos_test, 0, 1000);
    tcase_add_loop_test(tc1, tan_test, 0, 1000);
    tcase_add_loop_test(tc1, ln_test, 0, 1000);
    tcase_add_loop_test(tc1, sqrt_test, 0, 1000);
    tcase_add_loop_test(tc1, pow_test, 0, 1000);
    tcase_add_test(tc1, arifmetic_test);
    tcase_add_test(tc1, incorrect_test);
    tcase_add_test(tc1, error_test);

    srunner_set_fork_status (sr, CK_NOFORK);
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}

