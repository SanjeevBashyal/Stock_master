#ifndef HTML_H
#define HTML_H


#include"sqlite_database.h"
#include<QDateTime>
#include<QList>
#include<QStringList>
#include<QRegExp>
#include "ui_mainwindow.h"

class Html
{
public:
    Ui::MainWindow *mw=nullptr;
    Database db;
    Database db2;
    Database db3;
    QDate date=QDate::currentDate();
//    QString date=QDateTime::currentDateTime().date().toString("yyyy-MM-dd");

public:
    Html();
    bool get_and_save(QByteArray,int,int);
    bool get_and_save(QByteArray,int,QString);
    bool get_and_save(QList<QByteArray>,int,int);
    bool cross_check(QByteArray);
    bool get_marketdepth(QByteArray);
    int get_index(QJsonArray,QString);
    QString get_table(QString,int);
    QString get_merolagani_table(QString);
    QList<QStringList> parse_table(QString);
    QList<QList<QStringList>> special_parse_table(QString);
    QList<QList<QStringList>> super_special_parser_table(QString);
    QList<QStringList> beautify_table_parsed(QList<QStringList>);
    QList<QList<QStringList>> beautify_special_table_parsed(QList<QList<QStringList>>);
    QString get_text(QString,QString);

protected:
    bool save_stocks(QByteArray);
    bool save_stock_shares(QByteArray,int);
    bool save_merolagani(QByteArray,QString);
    bool save_todays_price(QList<QByteArray>);
    bool save_sharesansar(QByteArray,QString);
    bool save_sharesansar_id(QByteArray,QString);
    bool show_events(QByteArray, int, QString);
    bool show_reports(QByteArray, int, QString);
    bool save_dividends(QByteArray, int, QString);
    bool save_demand_supply(QByteArray);
};

#endif // HTML_H
