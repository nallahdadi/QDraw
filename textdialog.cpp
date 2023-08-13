#include "textdialog.h"
#include "ui_textdialog.h"

TextDialog::TextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextDialog)
{
    ui->setupUi(this);
    ui->textEdit->setText("Salam :)");
}

TextDialog::~TextDialog()
{
    delete ui;
}

void TextDialog::accept()
{
    text = ui->textEdit->toPlainText();
    QDialog::accept();
    update();
}
