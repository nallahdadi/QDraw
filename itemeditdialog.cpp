#include "itemeditdialog.h"
#include "ui_itemeditdialog.h"
#include <QColorDialog>
#include <QPixmap>

ItemEditDialog::ItemEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemEditDialog)
{
    ui->setupUi(this);
}

ItemEditDialog::~ItemEditDialog()
{
    delete ui;
}

void ItemEditDialog::customColorAct()
{
    QColorDialog colorDlg(this);
    colorDlg.show();
    if(colorDlg.exec() == QDialog::Accepted)
    {
        ui->customButton->setText("");
        ui->customButton->setStyleSheet(QObject::tr("background-color: %1").arg(colorDlg.selectedColor().name()));
        //ui->customButton->
    }
    ui->bColorcomboBox->setCurrentIndex(8);
    emit customBtClick(colorDlg.selectedColor());
}
