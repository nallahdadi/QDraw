#include "arcdialog.h"
#include "ui_arcDialog.h"

arcDialog::arcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::arcDialog)
{
    startAngle = spanAngle = 0;
    width = height = 10;
    ui->setupUi(this);
}

arcDialog::~arcDialog()
{
    delete ui;
}

void arcDialog::accept()
{
   spanAngle  = ui->spanSpin->value();
   startAngle = ui->startSpin->value();
   width       = ui->widthSpin->value();
   height     = ui->heightSpin->value();
   QDialog::accept();
   update();
}

int arcDialog::getType()
{
    if(ui->arcRadio->isChecked())
        return 1;
    else if(ui->pieRadio->isChecked())
        return 2;
    else if(ui->chordRadio->isChecked())
        return 3;
    else
        return 0;
    update();
}
