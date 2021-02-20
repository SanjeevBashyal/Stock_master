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
    void on_push_sss_clicked();     //sharesansar_book_close_date

    void on_push_tp_clicked();      //todays_price

    void on_push_ds_clicked();      //demand_supply

    void on_push_ml_clicked();      //merolagani_snatcher

    void on_push_ns_clicked();      //news_snatcher_sharesansar

    void on_line_news_returnPressed();      //news_snatching_tools

    void on_line_reports_returnPressed();   //reports_snatching_tools

    void on_push_qr_clicked();      //quarterly_reports_snatcher_sharesansar

    void on_push_news_enlarge_clicked();    //enlarge_news

    void on_push_reports_enlarge_clicked(); //enlarge reports

    void on_push_bd_clicked();      //bonus_dividend_snatching_from_sharesansar

    void on_push_ts_clicked();      //test_function

    void on_push_ss_clicked();      //stock_snatcher_nepse

    void on_push_pss_clicked();      //promoter_stock_snatcher_nepse

    void on_push_nse_clicked();     //Shares_outstanding_snatcher_NEPSE

public:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
