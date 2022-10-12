#include "deposit.h"
#include "ui_deposit.h"
#include "math.h"
#include <qdynamicbutton.h>

Deposit::Deposit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Deposit) {
    ui->setupUi(this);
}

Deposit::~Deposit() {
    delete ui;
}

void Deposit::on_add_replenishmen_clicked() {
    QDynamicButton *button = new QDynamicButton(this);
    ui->verticalLayout_2->addWidget(button);
}

void Deposit::on_add_withdrawal_clicked() {
    QDynamicButton *line_edit = new QDynamicButton(this);
    ui->verticalLayout_3->addWidget(line_edit);
}

void Deposit::on_delete_replenishmen_clicked() {
    if (ui->verticalLayout_2->count() > 1) {
        QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->verticalLayout_2->
            itemAt(ui->verticalLayout_2->count() - 1)->widget());
        button->hide();
        delete button;
    }
}

void Deposit::on_delete_withdrawal_clicked() {
    if (ui->verticalLayout_3->count() > 1) {
        QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->verticalLayout_3->
            itemAt(ui->verticalLayout_3->count() - 1)->widget());
        button->hide();
        delete button;
    }
}

void Deposit::on_calculate_contribution_clicked() {
    double deposit_amount = ui->deposit_amount->text().toDouble();
    double term = ui->term->text().toDouble();
    double rate = ui->rate->text().toDouble();
    double non_taxable = ui->tax_rate->text().toDouble() / 100 * 1000000;
    bool capitalization = ui->capitalization->isChecked();
    double amount_end = 0;

    double interest_charges = 0;
    double tax = 0;

    if (capitalization) {
        double count = 0;
        if (ui->every_day->isChecked()) {
            count = 365;
            term *= 31;
        } else if (ui->every_week->isChecked()) {
            count = 52;
            term *= 4 + 1;
        } else if (ui->once_month->isChecked()) {
            count = 12;
        } else if (ui->once_quarter->isChecked()) {
            count = 4;
            term = ceil(term / 3);
        } else if (ui->semiannually->isChecked()) {
            count = 2;
            term = ceil(term / 6);
        } else if (ui->once_year->isChecked()) {
            count = 1;
            term = ceil(term / 12);
        } else if (ui->at_the_end->isChecked()) {
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

    ui->interest_charges->setText(QString::number(interest_charges, 'f', 7));
    ui->tax_amount->setText(QString::number(tax, 'f', 7));
    ui->amount_end->setText(QString::number(amount_end, 'f', 7));
}
