#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "nepse.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Nepse ns;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    bool set_req_ui(Ui::MainWindow *);
    bool defaults();


public slots:


private slots:
    void on_push_sss_clicked();

    void on_push_tp_clicked();

    void on_push_ds_clicked();

    void on_push_ml_clicked();

    void on_push_ns_clicked();

    void on_line_news_returnPressed();

    void on_push_qr_clicked();

    void on_push_news_enlarge_clicked();

    void on_push_bd_clicked();

    void on_push_ts_clicked();

    void on_push_ss_clicked();
    void on_push_nse_clicked();

public:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
