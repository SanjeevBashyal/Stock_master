#include "nepse.h"


bool Nepse::add_stocks_to_quarterly_reports()
{
    QList<QStringList> symbols=this->rq.htm.db.to_list(this->rq.htm.db.query_select("select ID,Symbol,Security,Sector from Stock where Type='Equity' and (Status='A' or Status='S')"));

    for(int i=0;i<symbols.size();i++){
        QSqlQuery qry(this->rq.htm.db.db);
        qry.prepare("insert into quarterly_reports values(?,?,?,?,?,?)");
        qry.addBindValue(symbols[i][0]);
        qry.addBindValue(symbols[i][1]);
        qry.addBindValue(symbols[i][2]);
        qry.addBindValue(symbols[i][3]);
        qry.addBindValue(0);
        qry.addBindValue(0);
        this->mw->text_update->append(QString::number(314)+":"+QVariant(qry.exec()).toString());
        qry.clear();
    }
    return true;
}
