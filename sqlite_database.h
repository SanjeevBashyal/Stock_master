#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QVariant>
#include <QList>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

class Database
{

public:
    QSqlDatabase db;
public:
    Database(QString,QString);
    ~Database();
    QSqlQuery query_select(QString);
    QList<QStringList> to_list(QSqlQuery);
//    QList<QStringList> to_list_query_select(QString);
};

#endif // DATABASE_H
