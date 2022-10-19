#ifndef SMARTCALCMAINVIEW_H
#define SMARTCALCMAINVIEW_H

#include <QMainWindow>
#include "smartCalcController.h"
#include <algorithm>
#include <cctype>
#include <QRegularExpressionValidator>
#include <QVector>
#include <qdynamicbutton.h>

QT_BEGIN_NAMESPACE
namespace Ui { class SmartCalcMainView; }
QT_END_NAMESPACE

class SmartCalcMainView : public QMainWindow
{
    Q_OBJECT

public:
    SmartCalcMainView(SmartCalcController *c, QWidget *parent = nullptr);
    ~SmartCalcMainView();

private:
    Ui::SmartCalcMainView *ui;
    SmartCalcController *controller;
    QString change_op();

private slots:
   void digits_numbers();
   void on_button_dot_clicked();
   void on_button_reset_clicked();
   void on_button_sum_clicked();
   void on_button_sub_clicked();
   void on_button_mul_clicked();
   void on_button_div_clicked();
   void on_button_mod_clicked();
   void on_button_sqrt_clicked();
   void on_button_ln_clicked();
   void on_button_log_clicked();
   void on_button_tan_clicked();
   void on_button_atan_clicked();
   void on_button_cos_clicked();
   void on_button_acos_clicked();
   void on_button_sin_clicked();
   void on_button_asin_clicked();
   void on_button_op_bracket_clicked();
   void on_button_cl_bracket_clicked();
   void on_button_eq_clicked();
   void on_button_x_clicked();
   void on_button_pow_clicked();
   void on_button_clear_clicked();
   void on_build_graph_clicked();
   void on_tabWidget_currentChanged(int index);
   void on_graph_move_clicked();
   void on_credit_clicked();
   void on_calculate_contribution_2_clicked();
   void on_add_replenishmen_2_clicked();
   void on_add_withdrawal_2_clicked();
   void on_delete_replenishmen_2_clicked();
   void on_delete_withdrawal_2_clicked();
   void on_result_returnPressed();
};
#endif // SMARTCALCMAINVIEW_H
