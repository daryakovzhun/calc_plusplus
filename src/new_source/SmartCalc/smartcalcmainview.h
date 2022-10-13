#ifndef SMARTCALCMAINVIEW_H
#define SMARTCALCMAINVIEW_H

#include <QMainWindow>
#include "smartCalcController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SmartCalcMainView; }
QT_END_NAMESPACE

class SmartCalcMainView : public QMainWindow
{
    Q_OBJECT

public:
    SmartCalcMainView(SmartCalcController *c):controller(c){};
    SmartCalcMainView(QWidget *parent = nullptr);
    ~SmartCalcMainView();

private:
    Ui::SmartCalcMainView *ui;
    SmartCalcController *controller;
};
#endif // SMARTCALCMAINVIEW_H
