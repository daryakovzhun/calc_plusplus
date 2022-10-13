#include "smartCalcMainView.h"
#include "ui_smartcalcmainview.h"

SmartCalcMainView::SmartCalcMainView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartCalcMainView)
{
    ui->setupUi(this);
}

SmartCalcMainView::~SmartCalcMainView()
{
    delete ui;
}

