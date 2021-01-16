#ifndef NEPSE_H
#define NEPSE_H

#include "sqlite_database.h"
#include "request.h"
#include "nepse_calc.h"


class Nepse
{

public:
    Request rq;
    Nepse_calc nc;
    QString date=QDateTime::currentDateTime().date().toString("yyyy-MM-dd");
public:

public:
    Nepse();
    int snatch_stocks();
    int snatch_stock_shares();
    int snatch_from_merolagani();
    int snatch_todays_price();
    int snatch_from_sharesansar();
    int snatch_demand_supply();
    int snatch_events(int);
    int snatch_reports(int);
    int snatch_dividends(int);
    int snatch_stock_price(QString symbol,QString start,QString end);

public:
    int calc_roe(int);
    int calc_ros(int);
    QList<QStringList> add_zero(QList<QStringList>);

};

#endif // NEPSE_H
