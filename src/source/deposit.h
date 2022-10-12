#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>

namespace Ui {
class Deposit;
}

class Deposit : public QDialog
{
    Q_OBJECT

public:
    explicit Deposit(QWidget *parent = nullptr);
    ~Deposit();

private slots:
    void on_add_replenishmen_clicked();
    void on_add_withdrawal_clicked();
    void on_delete_replenishmen_clicked();

    void on_delete_withdrawal_clicked();

    void on_calculate_contribution_clicked();

private:
    Ui::Deposit *ui;
};

#endif // DEPOSIT_H
