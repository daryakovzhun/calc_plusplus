#ifndef QDYNAMICBUTTON_H
#define QDYNAMICBUTTON_H

#include <QLineEdit>

namespace Ui {
class QDynamicButton;
}

class QDynamicButton : public QLineEdit {
     Q_OBJECT
public:
    explicit QDynamicButton(QWidget *parent = 0);
    ~QDynamicButton();
    static int ResID;
    int getID();

private:
    int buttonID = 0;
};

#endif // QDYNAMICBUTTON_H
