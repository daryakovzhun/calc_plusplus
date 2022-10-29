#include "smartcalcmainview.h"
#include "ui_smartcalcmainview.h"

SmartCalcMainView::SmartCalcMainView(SmartCalcController *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SmartCalcMainView), controller(c)
{
    ui->setupUi(this);
    ui->result->setMaxLength(255);

    ui->enter_x->setValidator(new QRegularExpressionValidator(
        QRegularExpression("(^[-0-9])([0-9]*)(\\.?)([0-9]*)"), this));
    ui->xmin->setValidator(new QRegularExpressionValidator(
        QRegularExpression("(^[-0-9])([0-9]*)(\\.?)([0-9]*)"), this));
    ui->xmax->setValidator(new QRegularExpressionValidator(
        QRegularExpression("(^[-0-9])([0-9]*)(\\.?)([0-9]*)"), this));
    ui->step->setValidator(new QRegularExpressionValidator(
        QRegularExpression("([0-9]*)(\\.?)([0-9]*)"), this));

    connect(ui->button_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->button_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->button_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->button_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->button_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->button_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->button_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->button_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->button_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->button_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    ui->result->setFocus();
}

SmartCalcMainView::~SmartCalcMainView()
{
    delete ui;
}

void SmartCalcMainView::digits_numbers() {
    QPushButton *button = (QPushButton *)sender();

    if (ui->result->hasFocus()) {
        QString new_label =  ui->result->text() + button->text();
        ui->result->setText(new_label);
    } else if (ui->enter_x->hasFocus()) {
        QString new_label =  ui->enter_x->text() + button->text();
        ui->enter_x->setText(new_label);
    }
}

void SmartCalcMainView::on_button_dot_clicked() {
    ui->result->setText(ui->result->text() + ".");
}

void SmartCalcMainView::on_button_reset_clicked() {
    if (ui->result->hasFocus()) {
        ui->result->setText("");
    } else if (ui->enter_x->hasFocus()) {
        ui->enter_x->setText("");
    } 
}

void SmartCalcMainView::on_button_clear_clicked() {
    std::string str;
    if (ui->result->hasFocus()) {
        str = ui->result->text().toStdString();

        std::string op = "+-*/";
        size_t len = str.size();
        if (len > 0) {
            if (std::count(op.begin(), op.end(), str[len - 1]) || str[str.size() - 1] == ')') {
                str.erase(str.size() - 1);
            } else if (isdigit(str[str.size() - 1]) || str[str.size() - 1] == '.') {
                while (len > 0 && (isdigit(str[str.size() - 1]) || str[str.size() - 1] == '.')) {
                    str.erase(str.size() - 1);
                    len = str.size();
                }
            } else {
                if (str[str.size() - 1] == '(') {
                    str.erase(str.size() - 1);
                }
                while (len > 0 && (isalpha(str[str.size() - 1]) || str[str.size() - 1] == '^')) {
                    str.erase(str.size() - 1);
                    len = str.size();
                }
            }
        }
        ui->result->setText(QString::fromStdString(str));
    } else if (ui->enter_x->hasFocus()) {
        str = ui->enter_x->text().toStdString();
        if (str.size() > 0) { str.erase(str.size() - 1);} 
        ui->enter_x->setText(QString::fromStdString(str));
    }
}

QString SmartCalcMainView::change_op() {
    QString str = ui->result->text();
    std::string op = "+-*/";
    size_t len = str.size();
    if (len > 0 && std::count(op.begin(), op.end(), str[len - 1])) {
        str.chop(1);
    }
    return str;
}

void SmartCalcMainView::on_button_sum_clicked() {
    ui->result->setText(change_op() + "+");
}

void SmartCalcMainView::on_button_sub_clicked() {
    ui->result->setText(change_op() + "-");
}

void SmartCalcMainView::on_button_mul_clicked() {
    ui->result->setText(change_op() + "*");
}

void SmartCalcMainView::on_button_div_clicked() {
    ui->result->setText(change_op() + "/");
}

void SmartCalcMainView::on_button_mod_clicked() {
    ui->result->setText(ui->result->text() + "mod");
}

void SmartCalcMainView::on_button_sqrt_clicked() {
    ui->result->setText(ui->result->text() + "sqrt(");
}

void SmartCalcMainView::on_button_ln_clicked() {
    ui->result->setText(ui->result->text() + "ln(");
}

void SmartCalcMainView::on_button_log_clicked() {
    ui->result->setText(ui->result->text() + "log(");
}

void SmartCalcMainView::on_button_tan_clicked() {
    ui->result->setText(ui->result->text() + "tan(");
}

void SmartCalcMainView::on_button_atan_clicked() {
    ui->result->setText(ui->result->text() + "atan(");
}

void SmartCalcMainView::on_button_cos_clicked() {
    ui->result->setText(ui->result->text() + "cos(");
}

void SmartCalcMainView::on_button_acos_clicked() {
    ui->result->setText(ui->result->text() + "acos(");
}

void SmartCalcMainView::on_button_sin_clicked() {
    ui->result->setText(ui->result->text() + "sin(");
}

void SmartCalcMainView::on_button_asin_clicked() {
    ui->result->setText(ui->result->text() + "asin(");
}

void SmartCalcMainView::on_button_pow_clicked() {
    ui->result->setText(change_op() + "^(");
}

void SmartCalcMainView::on_button_op_bracket_clicked() {
    ui->result->setText(ui->result->text() + "(");
}

void SmartCalcMainView::on_button_cl_bracket_clicked() {
    ui->result->setText(ui->result->text() + ")");
}

void SmartCalcMainView::on_button_x_clicked() {
    ui->result->setText(ui->result->text() + "x");
}

void SmartCalcMainView::on_button_eq_clicked() {
    std::string expression = ui->result->text().toStdString();
    controller->set_expression(expression);
    controller->set_x(ui->enter_x->text().toDouble());
    try {
        double result = controller->get_result();
        ui->result->setText(QString::number(result, 'f'));
    } catch(const std::exception& e) {
        ui->result->setText("Error");
    }

    controller->reset();
}

void SmartCalcMainView::on_tabWidget_currentChanged(int index)
{
    if (index == 1) {
        if (ui->result->text().length()) {
            ui->expression->setText("y = " + ui->result->text());
        } else {
            ui->expression->setText("y = expression");
        }
    }
}

void SmartCalcMainView::on_build_graph_clicked() {
    ui->graph->clearGraphs();

    if (ui->result->text().length() > 0) {
        double a = -10, b = 10, h = 1;
        if (ui->xmin->text().length() != 0) a = ui->xmin->text().toDouble();
        if (ui->xmax->text().length() != 0) b = ui->xmax->text().toDouble();
        if (ui->step->text().length() != 0) h = ui->step->text().toDouble();

        if (a > b || h <= 0) {
            a = 0;
            b = 0;
            h = 1;
        }

        if (a < -100000) { a = -100000; }
        if (b > 100000) { b = 100000; }

        int N = (b - a) / h + 2;

        if (N > 1000000) {
            N = 1000000;
            h = (b - a) / (N - 2);
        }

        QVector<double> x(N), y(N);
        controller->set_expression(ui->result->text().toStdString());

        int i = 0;
        for (double X = a; X <= b; X += h) {
          controller->set_x(X);
          try {
              y[i] = controller->get_result();
          } catch(const std::exception& e) {
              continue;
          }
          x[i] = X;
          i++;
        }
        ui->graph->clearGraphs();
        ui->graph->addGraph();

        ui->graph->graph(0)->setData(x, y);
        ui->graph->graph(0)->setPen(QColor(50, 50, 50, 255));
        ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

        ui->graph->xAxis->setLabel("x");
        ui->graph->yAxis->setLabel("y");
        ui->graph->xAxis->setRange(a, b);

        double minY = y[0], maxY = y[0];
        for (int i = 1; i < N; i++) {
          if (y[i] <= minY) minY = y[i] - 1;
          if (y[i] >= maxY) maxY = y[i] + 1;
        }
        ui->graph->yAxis->setRange(minY, maxY);
        ui->graph->replot();
        controller->reset();
    }
}

void SmartCalcMainView::on_graph_move_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
    on_build_graph_clicked();
}




void SmartCalcMainView::on_credit_clicked()
{
    double total_amount = ui->totalamount->text().toDouble();
    double term = ui->term->text().toDouble() * 12;
    double rate = ui->rate->text().toDouble() / 100;
    double month_payment = 0;
    double overpayment = 0;

    if (total_amount && term && rate && total_amount > 0 && term > 0 && total_amount > 0) {
        if (ui->annuity->isChecked()) {
            double rate_month = rate / 12;
            month_payment = total_amount * (rate_month / (1 - pow((1 + rate_month), -term)));
            overpayment = (month_payment * term) - total_amount;

            ui->month_payment->setText(QString::number(month_payment, 'f', 7));
        } else if (ui->differentiated->isChecked()) {
            month_payment = total_amount / term;
            double overpayment_month = 0;

            for (int i = 0; i < term; i++) {
                overpayment_month = total_amount * rate / 12;

                if (i == 0) {
                    ui->month_payment->setText(QString::number(month_payment +
                        overpayment_month, 'f', 3) + "..");
                }
                if (i == term - 1) {
                    ui->month_payment->setText(ui->month_payment->text() +
                        QString::number(month_payment + overpayment_month, 'f', 3));
                }
                overpayment += overpayment_month;
                total_amount -= month_payment;
            }
            total_amount = month_payment * term;
        }
        ui->overpayment->setText(QString::number(overpayment, 'f', 3));
        ui->total_payout->setText(QString::number(total_amount + overpayment, 'f', 3));
    }
}

void SmartCalcMainView::on_add_replenishmen_2_clicked() {
    QDynamicButton *button = new QDynamicButton(this);
    ui->verticalLayout_7->addWidget(button);
}

void SmartCalcMainView::on_add_withdrawal_2_clicked() {
    QDynamicButton *line_edit = new QDynamicButton(this);
    ui->verticalLayout_8->addWidget(line_edit);
}

void SmartCalcMainView::on_delete_replenishmen_2_clicked() {
    if (ui->verticalLayout_7->count() > 1) {
        QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->verticalLayout_7->
            itemAt(ui->verticalLayout_7->count() - 1)->widget());
        button->hide();
        delete button;
    }
}

void SmartCalcMainView::on_delete_withdrawal_2_clicked() {
    if (ui->verticalLayout_8->count() > 1) {
        QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->verticalLayout_8->
            itemAt(ui->verticalLayout_8->count() - 1)->widget());
        button->hide();
        delete button;
    }
}

void SmartCalcMainView::on_calculate_contribution_2_clicked()
{
    double deposit_amount = ui->deposit_amount_2->text().toDouble();
    double term = ui->term_3->text().toDouble();
    double rate = ui->rate_3->text().toDouble();
    double non_taxable = ui->tax_rate_2->text().toDouble() / 100 * 1000000;
    bool capitalization = ui->capitalization_2->isChecked();
    double amount_end = 0;

    double interest_charges = 0;
    double tax = 0;

    if (capitalization) {
        double count = 0;
        if (ui->frequency->currentIndex() == 0) {
            count = 365;
            term *= 31;
        } else if (ui->frequency->currentIndex() == 1) {
            count = 52;
            term *= 4 + 1;
        } else if (ui->frequency->currentIndex() == 2) {
            count = 12;
        } else if (ui->frequency->currentIndex() == 3) {
            count = 4;
            term = ceil(term / 3);
        } else if (ui->frequency->currentIndex() == 4) {
            count = 2;
            term = ceil(term / 6);
        } else if (ui->frequency->currentIndex() == 5) {
            count = 1;
            term = ceil(term / 12);
        } else if (ui->frequency->currentIndex() == 6) {
            count = term;
        }

        if (count) {
            amount_end = deposit_amount * pow((1 + (rate / 100) / count), term);
            interest_charges = amount_end - deposit_amount;
            tax = (interest_charges - non_taxable) * 0.13;
        }

    } else {
        interest_charges = deposit_amount * rate * term * 31 / 365 / 100;
        tax = (interest_charges - non_taxable) * 0.13;
        amount_end = deposit_amount;
    }

    ui->interest_charges_2->setText(QString::number(interest_charges, 'f', 7));
    ui->tax_amount_2->setText(QString::number(tax, 'f', 7));
    ui->amount_end_2->setText(QString::number(amount_end, 'f', 7));
}

void SmartCalcMainView::on_result_returnPressed()
{
    on_button_eq_clicked();
}

