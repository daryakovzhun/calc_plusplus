#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include "credit.h"
#include "deposit.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->result->setMaxLength(255);
    ui->result->setReadOnly(true);

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
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::digits_numbers() {
    QPushButton *button = (QPushButton *)sender();
    QString new_label =  ui->result->text() + button->text();

    ui->result->setText(new_label);
}


void MainWindow::on_button_dot_clicked() {
    QString number;
    int i, k = 0, len = ui->result->text().length();
    number.resize(len + 1);

    for (i = len - 1; i >= 0; i--) {
        number[k++] = ui->result->text()[i];
        if (ui->result->text()[i] == ' ' || ui->result->text()[i] == '(') {
            number[k++] = '\0';
            break;
        }
    }

    if (!(number.contains('.')))
        ui->result->setText(ui->result->text() + ".");
    number.clear();
}

void MainWindow::on_button_reset_clicked() {
    ui->result->setText("");
}

void MainWindow::on_button_clear_clicked() {
    QString str = ui->result->text();
    int len = str.length();
    if (len > 0 && (str[len - 1] == '(' || str[len - 1] == ' ')) {
        if (str[len - 1] == ' ' || str[len - 1] == '(') {
            str.chop(1);
            len = str.length();
        }
        while (len > 0 && str[len - 1] != ' ' && str[len - 1] != '('
                    && str[len - 1] != '+' && str[len - 1] != '-') {
            str.chop(1);
            len = str.length();
        }
    } else {
        str.chop(1);
    }
    ui->result->setText(str);
    str.clear();
}

void MainWindow::on_button_sum_clicked() {
    QString str = ui->result->text();
    int len = str.length();

    if (len == 0 || (len == 1 && str[len - 1] == '-') || str[len - 1] == '(') {
        if (len > 0 && str[len - 1] == '(') {
            ui->result->setText(str + "+");
        } else {
            ui->result->setText("+");
        }
    } else {
        if (len > 0 && str[len - 1] == '-') {
            str.chop(1);
            ui->result->setText(str + "+");
        } else {
            if (len >= 2 && str[len - 2] == '-' && str[len - 1] == ' ') {
                str.chop(3);
            }
            ui->result->setText(str + " + ");
        }
    }
    str.clear();
}

void MainWindow::on_button_sub_clicked() {
    QString str = ui->result->text();
    int len = str.length();

    if (len == 0 || (len == 1 && str[len - 1] == '+') || str[len - 1] == '(') {
        if (len > 0 && str[len - 1] == '(') {
            ui->result->setText(str + "-");
        } else {
            ui->result->setText("-");
        }
    } else {
        if (len > 0 && str[len - 1] == '+') {
            str.chop(1);
            ui->result->setText(str + "-");
        } else {
            if (len >= 2 && str[len - 2] == '+' && str[len - 1] == ' ') {
                str.chop(3);
            }
            ui->result->setText(str + " - ");
        }
    }
    str.clear();
}

void MainWindow::on_button_mul_clicked() {
    QString str = ui->result->text();
    int len = str.length();
    if (len > 2 && str[len - 1] == ' ' && (str[len - 2] == '/'
            || str[len - 2] == '+' || str[len - 2] == '-')) {
        str.chop(3);
    }
    ui->result->setText(str + " * ");
    str.clear();
}

void MainWindow::on_button_div_clicked() {
    QString str = ui->result->text();
    int len = str.length();
    if (len > 2 && str[len - 1] == ' ' && (str[len - 2] == '*'
            || str[len - 2] == '+' || str[len - 2] == '-')) {
        str.chop(3);
    }
    ui->result->setText(str + " / ");
    str.clear();
}

void MainWindow::on_button_mod_clicked() {
    ui->result->setText(ui->result->text() + " mod ");
}

void MainWindow::on_button_sqrt_clicked() {
    ui->result->setText(ui->result->text() + "sqrt(");
}

void MainWindow::on_button_ln_clicked() {
    ui->result->setText(ui->result->text() + "ln(");
}

void MainWindow::on_button_log_clicked() {
    ui->result->setText(ui->result->text() + "log(");
}

void MainWindow::on_button_tan_clicked() {
    ui->result->setText(ui->result->text() + "tan(");
}

void MainWindow::on_button_atan_clicked() {
    ui->result->setText(ui->result->text() + "atan(");
}

void MainWindow::on_button_cos_clicked() {
    ui->result->setText(ui->result->text() + "cos(");
}

void MainWindow::on_button_acos_clicked() {
    ui->result->setText(ui->result->text() + "acos(");
}

void MainWindow::on_button_sin_clicked() {
    ui->result->setText(ui->result->text() + "sin(");
}

void MainWindow::on_button_asin_clicked() {
    ui->result->setText(ui->result->text() + "asin(");
}

void MainWindow::on_button_pow_clicked() {
    ui->result->setText(ui->result->text() + "^(");
}

void MainWindow::on_button_op_bracket_clicked() {
    ui->result->setText(ui->result->text() + "(");
}

void MainWindow::on_button_cl_bracket_clicked() {
    ui->result->setText(ui->result->text() + ")");
}

void MainWindow::on_button_x_clicked() {
    int len = ui->result->text().length();
    if ((len > 0 && ui->result->text()[len - 1] != 'x') || len == 0) {
        ui->result->setText(ui->result->text() + "x");
    }
}

void MainWindow::on_button_eq_clicked() {
    if (ui->result->text().length() > 0) {
        std::string str = ui->result->text().toStdString();
        const char* p = str.c_str();
        char result[226];
        if (strchr(p, 'x')) {
            ui->result->setText("Incorrect expression");
        } else {
            compute(p, result, 0);
            ui->result->setText(result);
        }
    }
}

void MainWindow::on_button_graph_clicked() {
    Graph window;
    window.setLabel(ui->result->text());
    window.setModal(true);
    window.setWindowTitle("Graph");
    window.exec();
}


void MainWindow::on_button_credit_clicked() {
    Credit window;
    window.setModal(true);
    window.setWindowTitle("Credit calculator");
    window.exec();
}

void MainWindow::on_button_deposit_clicked() {
    Deposit window;
    window.setModal(true);
    window.setWindowTitle("Deposit calculator");
    window.exec();
}
