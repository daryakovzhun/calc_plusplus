#include <QApplication>

#include "smartcalcmainview.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  SmartCalcModel model;
  SmartCalcController controller(&model);
  SmartCalcMainView view(&controller);
  view.show();
  return a.exec();
}
