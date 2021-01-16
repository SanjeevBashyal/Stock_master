#include "sqlite_database.h"

Database::Database(QString path, QString name)
{
    this->db=QSqlDatabase::addDatabase("QSQLITE",name);
    this->db.setDatabaseName(path);
    this->db.open();
}

Database::~Database()
{
    QSqlDatabase::removeDatabase(this->db.connectionName());
}

QSqlQuery Database::query_select(QString str)
{
    QSqlQuery qry(this->db);
    qry.exec(str);
    return qry;
}

QList<QStringList> Database::to_list(QSqlQuery qry)
{
    int col=qry.record().count();
    QList<QStringList> out;
    while(qry.next()){
        QStringList tr;
        for (int j=0;j<col;j++){
            QString td=qry.value(j).toString();
            tr<<td;
        }
        out<<tr;
    }
//    qry.finish();
    return out;
}
