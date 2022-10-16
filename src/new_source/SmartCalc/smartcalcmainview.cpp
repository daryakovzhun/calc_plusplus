#include "smartcalcmainview.h"
#include "ui_smartcalcmainview.h"

SmartCalcMainView::SmartCalcMainView(SmartCalcController *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SmartCalcMainView), controller(c)
{
    ui->setupUi(this);
    ui->result->setMaxLength(255);
//    ui->result->setReadOnly(true);
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
}

SmartCalcMainView::~SmartCalcMainView()
{
    delete ui;
}

void SmartCalcMainView::digits_numbers() {
    QPushButton *button = (QPushButton *)sender();
    QString new_label =  ui->result->text() + button->text();

    ui->result->setText(new_label);
}

void SmartCalcMainView::on_button_dot_clicked() {
    ui->result->setText(ui->result->text() + ".");
}

void SmartCalcMainView::on_button_reset_clicked() {
    ui->result->setText("");
}

void SmartCalcMainView::on_button_clear_clicked() {
    std::string str = ui->result->text().toStdString();
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
    int len = ui->result->text().length();
    if ((len > 0 && ui->result->text()[len - 1] != 'x') || len == 0) {
        ui->result->setText(ui->result->text() + "x");
    }
}

void SmartCalcMainView::on_button_eq_clicked() {
    if (ui->result->text().length() > 0) {
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

void SmartCalcMainView::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
    on_build_graph_clicked();
}
