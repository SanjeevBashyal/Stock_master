#include "dialog_table.h"
#include "ui_dialog_table.h"

Dialog_table::Dialog_table(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_table)
{
    ui->setupUi(this);
}

Dialog_table::~Dialog_table()
{
    delete ui;
}
