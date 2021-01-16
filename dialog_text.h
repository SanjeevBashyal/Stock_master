#ifndef DIALOG_TEXT_H
#define DIALOG_TEXT_H

#include <QDialog>

namespace Ui {
class Dialog_text;
}

class Dialog_text : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_text(QWidget *parent = nullptr);
    ~Dialog_text();

public:
    void set_text(QString text);
    void save();

private:
    Ui::Dialog_text *ui;
};

#endif // DIALOG_TEXT_H
