#include <QApplication>

#include "smartCalcMainView.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  SmartCalcModel model;
  SmartCalcController controller(&model);
  SmartCalcMainView view(&controller);
  view.show();
  return a.exec();
}
