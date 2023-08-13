#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include <QDialog>

namespace Ui {
    class TextDialog;
}

class TextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextDialog(QWidget *parent = 0);
    QString text;
    ~TextDialog();


private:
    Ui::TextDialog *ui;
private slots:
    virtual void accept();
};

#endif // TEXTDIALOG_H
