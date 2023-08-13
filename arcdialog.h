#ifndef ARCDIALOG_H
#define ARCDIALOG_H

#include <QDialog>

namespace Ui {
    class arcDialog;
}

class arcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit arcDialog(QWidget *parent = 0);
    int getWidth() { return width;}
    int getHeight(){ return height;}
    int getStartAngle() {return startAngle;}
    int getSpanAngle()  {return spanAngle;}
    int getType();
    ~arcDialog();

private:
    Ui::arcDialog *ui;
    int startAngle, spanAngle, height, width;
private slots:
   void accept();
};

#endif // ARCDIALOG_H
