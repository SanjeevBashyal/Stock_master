#ifndef NEPSE_H
#define NEPSE_H

#include "sqlite_database.h"
#include "request.h"
#include "nepse_calc.h"
#include "ui_mainwindow.h"

#include <QString>
#include<QUrlQuery>


class Nepse
{

public:
    Request rq;
    Nepse_calc nc;
    int Year;
    int Quarter;
    QString date=QDateTime::currentDateTime().date().toString("yyyy-MM-dd");

public:
    Ui::MainWindow *mw=nullptr;

public:
    Nepse();
    int defaults();
    int snatch_stocks();
    int snatch_stock_shares();
    int snatch_from_merolagani();
    int snatch_todays_price();
    int snatch_from_sharesansar();
    int snatch_quarterly_reports_all(QString);
    int snatch_from_sharesansar_quarterly_reports(QString);
    int snatch_sharesansar_id();
    int snatch_demand_supply();
    int snatch_events(int);
    int snatch_reports(int);
    int snatch_dividends(int);
    int snatch_stock_price(QString symbol,QString start,QString end);

public:
    int calc_roe(int);
    int calc_ros(int);
    bool add_stocks_to_quarterly_reports();
    QList<QStringList> add_zero(QList<QStringList>);

};

#endif // NEPSE_H
