#ifndef DIALOG_TABLE_H
#define DIALOG_TABLE_H

#include <QDialog>

namespace Ui {
class Dialog_table;
}

class Dialog_table : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_table(QWidget *parent = nullptr);
    ~Dialog_table();

private:
    Ui::Dialog_table *ui;
};

#endif // DIALOG_TABLE_H
