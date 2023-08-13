#ifndef ITEMEDITDIALOG_H
#define ITEMEDITDIALOG_H

#include <QDialog>

namespace Ui {
class ItemEditDialog;
}

class ItemEditDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ItemEditDialog(QWidget *parent = 0);
    ~ItemEditDialog();

signals:
    void customBtClick(QColor eColor);

private slots:
    void customColorAct();
    
public:
    Ui::ItemEditDialog *ui;
};

#endif // ITEMEDITDIALOG_H
