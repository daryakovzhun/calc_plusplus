#include "credit.h"
#include "ui_credit.h"
#include "math.h"
#include <ctime>

Credit::Credit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Credit) {
    ui->setupUi(this);
}

Credit::~Credit() {
    delete ui;
}

void Credit::on_pushButton_clicked() {
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
            int count_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, j = 0;
            std::time_t t = std::time(nullptr);
            std:: tm *now = std::localtime(&t);
            j = now->tm_mon;

            for (int i = 0; i < term; i++) {
                overpayment_month = total_amount * rate * count_day[j++] / 365;

                if (i == 0) {
                    ui->month_payment->setText(QString::number(month_payment +
                        overpayment_month, 'f', 7) + "..");
                }
                if (i == term - 1) {
                    ui->month_payment->setText(ui->month_payment->text() +
                        QString::number(month_payment + overpayment_month, 'f', 7));
                }
                overpayment += overpayment_month;
                total_amount -= month_payment;

                if (j == 12) {
                    j = 0;
                }
            }
            total_amount = month_payment * term;
        }
        ui->overpayment->setText(QString::number(overpayment, 'f', 7));
        ui->total_payout->setText(QString::number(total_amount + overpayment, 'f', 7));
    }
}
