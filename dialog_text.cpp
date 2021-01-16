#include "dialog_text.h"
#include "ui_dialog_text.h"

Dialog_text::Dialog_text(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_text)
{
    ui->setupUi(this);
}

Dialog_text::~Dialog_text()
{
    delete ui;
}

void Dialog_text::set_text(QString text)
{
    this->ui->text_enlarge->setText(text);
}
