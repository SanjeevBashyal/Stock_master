#include "html.h"
#include "table_parser.h"
#include "special_table_parser.h"
#include "super_special_table_parser.h"
#include <QRegularExpression>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QDateTime>
Html::Html()
    :db("C:\\Users\\SANJEEV BASHYAL\\Desktop\\NEPSE\\NEPSE_\\Fundamental Analysis.db","FA")
    , db2("C:\\Users\\SANJEEV BASHYAL\\Desktop\\NEPSE\\NEPSE_\\Datastore.db","DS")
    , db3("C:\\Users\\SANJEEV BASHYAL\\Desktop\\NEPSE\\NEPSE_\\Others.db","O")
{

}

bool Html::get_and_save(QByteArray text, int iden, int id)
{
    QString a(text);
    if(a.isEmpty()){
        return false;
    }

    Q_UNUSED(id);

    if (iden==1){
        return this->save_stocks(text);
    }
    else if(iden==6){
        return this->save_stock_shares(text,id);
    }
    else if(iden==10){
        return this->save_demand_supply(text);
    }
//    else if(iden==2){

//    }
//    else if(iden==2){

//    }
    return false;
}

bool Html::get_and_save(QByteArray text,int iden, QString id)
{


    QString a(text);
    if(a.isEmpty()){
        return false;
    }

    if(iden==4){
        return this->save_merolagani(text,id);
    }
    else if(iden==5){
        return this->save_sharesansar(text,id);
    }
    else if(iden==7 || iden==70 || iden==700){
        return this->show_events(text,iden,id);
    }
    else if(iden==8 || iden==80 || iden==800){
        return this->show_reports(text,iden,id);
    }
    else if(iden==9 || iden==90 || iden==900){
        return this->save_dividends(text,iden,id);
    }
    else if(iden==2){

    }
    else if(iden==11){
        return this->save_sharesansar_id(text,id);
    }
    return false;
}

bool Html::get_and_save(QList<QByteArray> texts,int iden, int size)
{

    Q_UNUSED(size);
    if(iden==3){
        return this->save_todays_price(texts);
    }
//    else if(iden==2){
//        this->save_sharesansar(text,id);
//    }

    return false;
}


bool Html::save_stocks(QByteArray text)
{
    QJsonParseError parse_error;

    //read and parse from file
    QJsonDocument doc = QJsonDocument::fromJson(text,
                                               &parse_error);

    //check parsing errors
    if (parse_error.error != QJsonParseError::NoError) {
        qDebug() << "Parsing error:" << parse_error.errorString();
        return 1;
    }

    //this is top level arraya
    QJsonArray arr_companies = doc.array();

    //this is array of country objects
//    QJsonArray arr_companies = arr_doc[0].toArray();

    for(int i=0;i<arr_companies.size();i++){
        if(arr_companies.at(i)["status"].toString()=="A"){
            QSqlQuery qry(this->db.db);
            qry.prepare("insert into Stock (Symbol, Security, ID, Type, Sector) values(?,?,?,?,?)");
            qry.addBindValue(arr_companies.at(i)["symbol"].toString());
            qry.addBindValue(arr_companies.at(i)["securityName"].toString());
            qry.addBindValue(arr_companies.at(i)["id"].toInt(0));
            qry.addBindValue(arr_companies.at(i)["instrumentType"].toString());
            qry.addBindValue(arr_companies.at(i)["sectorName"].toString());
    //        qry.addBindValue(arr_companies.at(i)["regulatoryBody"].toString());
            qDebug()<<qry.exec();
        }

    }

    return true;

}

bool Html::save_stock_shares(QByteArray text, int id)
{
    text.insert(0,'[');
    text.insert(text.size(),']');

    QJsonParseError parse_error;

    //read and parse from file
    QJsonDocument doc = QJsonDocument::fromJson(text,
                                               &parse_error);

    //check parsing errors
    if (parse_error.error != QJsonParseError::NoError) {
        qDebug() << "Parsing error:" << parse_error.errorString();
        return 1;
    }

    //this is top level arraya
    QJsonArray arr_companies = doc.array();

    QSqlQuery qry(this->db.db);
    qry.prepare(QString("update Stock set Listed_Shares=?, Promoter=?, Public=? where ID=%1").arg(id));
    qry.addBindValue(arr_companies.at(0)["stockListedShares"].toInt());
    qry.addBindValue(arr_companies.at(0)["promoterPercentage"].toDouble(0));
    qry.addBindValue(arr_companies.at(0)["publicPercentage"].toDouble(0));
    return qry.exec();

}

bool Html::save_merolagani(QByteArray text, QString symbol){

    QRegExp re("<table class=\"table table-striped table-hover table-zeromargin\" id=\"accordion\">.+Market Capitalization.+</table>");
    re.setMinimal(true);
    re.indexIn(text);
    QString table=re.cap(0);

    QRegExp re1("ctl00_ContentPlaceHolder1_CompanyDetail1_lblMarketPrice.+>(.+)<");
    QRegExp re2("ctl00_ContentPlaceHolder1_CompanyDetail1_lblChange.+>(.+)<");
    QRegExp re3("Last Traded On.+<td.+>(.+)</td>");
    QRegExp re4("52 Weeks Low - High.+<td.+>(.+)</td>");
    QRegExp re5("180 Day Average.+<td.+>(.+)</td>");
    QRegExp re6("ctl00_ContentPlaceHolder1_CompanyDetail1_lblYearYeild.+>(.+)<");
    QRegExp re7("EPS.+<td.+>(.+)<span.+>(.+)</span>");
    QRegExp re8("P/E Ratio.+<td.+>(.+)</td>");
    QRegExp re9("Book Value.+<td.+>(.+)</td>");
    QRegExp re10("PBV.+<td.+>(.+)</td>");
//    QRegExp re11("% Dividend.+<td.+>(.+)<span.+>(.+)</span>");
//    QRegExp re12("% Bonus.+<td.+>(.+)<span.+>(.+)</span>");
    QRegExp re13("Right Share.+<td.+>(.+)<span.+>(.+)</span>");
    QRegExp re14("30-Day Avg Volume.+<td.+>(.+)</td>");
    QRegExp re15("Market Capitalization.+<td.+>(.+)</td>");



    re1.setMinimal(true);
    re2.setMinimal(true);
    re3.setMinimal(true);
    re4.setMinimal(true);
    re5.setMinimal(true);
    re6.setMinimal(true);
    re7.setMinimal(true);
    re8.setMinimal(true);
    re9.setMinimal(true);
    re10.setMinimal(true);
//    re11.setMinimal(true);
//    re12.setMinimal(true);
    re13.setMinimal(true);
    re14.setMinimal(true);
    re15.setMinimal(true);


    int pos = re1.indexIn(table);Q_UNUSED(pos);
    int pos2 = re2.indexIn(table);Q_UNUSED(pos2);
    int pos3 = re3.indexIn(table);Q_UNUSED(pos3);
    int pos4 = re4.indexIn(table);Q_UNUSED(pos4);
    int pos5 = re5.indexIn(table);Q_UNUSED(pos5);
    int pos6 = re6.indexIn(table);Q_UNUSED(pos6);
    int pos7 = re7.indexIn(table);Q_UNUSED(pos7);
    int pos8 = re8.indexIn(table);Q_UNUSED(pos8);
    int pos9 = re9.indexIn(table);Q_UNUSED(pos9);
    int pos10 = re10.indexIn(table);Q_UNUSED(pos10);
//    int pos11 = re11.indexIn(table);
//    int pos12 = re12.indexIn(table);
    int pos13 = re13.indexIn(table);Q_UNUSED(pos13);
    int pos14 = re14.indexIn(table);Q_UNUSED(pos14);
    int pos15 = re15.indexIn(table);Q_UNUSED(pos15);


    QString ts=re1.cap(1);ts.remove(',');
    QString ts2=re2.cap(1);ts2.chop(2);ts2.remove(',');
    QString ts3=re3.cap(1).simplified();ts3.chop(9);
    QString ts4=re4.cap(1).simplified();
    QString ts5=re5.cap(1).simplified();ts5.remove(',');
    QString ts6=re6.cap(1);ts6.chop(1);ts6.remove(',');
    QString ts7=(re7.cap(1)+re7.cap(2)).simplified();
    QString ts8=re8.cap(1).simplified();ts8.remove(',');
    QString ts9=re9.cap(1).simplified();ts9.remove(',');
    QString ts10=re10.cap(1).simplified();ts10.remove(',');
//    QString ts11=(re11.cap(1)+re11.cap(2)).simplified();
//    QString ts12=(re12.cap(1)+re12.cap(2)).simplified();
    QString ts13=(re13.cap(1)+re13.cap(2)).simplified();
    QString ts14=re14.cap(1).simplified();ts14.remove(',');
    QString ts15=re15.cap(1).simplified();ts15.remove(',');

    QSqlQuery qry(this->db.db);
    qry.prepare(QString("update Stock set Price=?, Change=?, Market_Capitalization=?, \"52_Weeks_High_Low\"=?, \"180_Day_Average\"=?, \"1_Year_Yield\"=?, EPS=?, PE_Ratio=?, Book_Value=?, PBV=?, Right_Share=?, \"30_Day_Avg_Volume\"=?, Last_Traded=? where Symbol='%1'").arg(symbol));

    qry.addBindValue(ts.toDouble(0));
    qry.addBindValue(ts2.toDouble(0));
    qry.addBindValue(ts15.toDouble(0));
    qry.addBindValue(ts4);
    qry.addBindValue(ts5.toDouble(0));
    qry.addBindValue(ts6.toDouble(0));
    qry.addBindValue(ts7);
    qry.addBindValue(ts8.toDouble(0));
    qry.addBindValue(ts9.toDouble(0));
    qry.addBindValue(ts10.toDouble(0));
//    qry.addBindValue(ts11);
//    qry.addBindValue(ts12);
    qry.addBindValue(ts13);
    qry.addBindValue(ts14.toDouble(0));
    qry.addBindValue(ts3);

    return qry.exec();
}

bool Html::save_todays_price(QList<QByteArray> texts)
{
    QString date=this->date.toString("yyyy-MM-dd");
    QByteArray text=texts[0];
    QByteArray text2=texts[1];

    QString a(text),a2(text2);
    if(a.isEmpty() || a2.isEmpty()){
        return false;
    }

    text.insert(0,'[');
    text.insert(text.size(),']');

    text2.insert(0,'[');
    text2.insert(text.size(),']');

    QJsonParseError parse_error;
    QJsonParseError parse_error2;

    //read and parse from file
    QJsonDocument doc = QJsonDocument::fromJson(text,
                                               &parse_error);

    QJsonDocument doc2 = QJsonDocument::fromJson(text2,
                                               &parse_error2);

    //check parsing errors
    if (parse_error.error != QJsonParseError::NoError && parse_error2.error != QJsonParseError::NoError) {
//        qDebug() << "Parsing error:" << parse_error.errorString();
        return 1;
    }

    QJsonArray arr_companies = doc.array().at(0)["content"].toArray();
    QJsonArray demand = doc2.array().at(0)["demandList"].toArray();
    QJsonArray supply = doc2.array().at(0)["supplyList"].toArray();
//    qDebug()<<arr_companies;
//    qDebug()<<demand;
//    qDebug()<<supply;

//    QString time=QDateTime::currentDateTime().time().toString("hh:mm");
    QStringList date_list,symbol_list,name_list;
    QVariantList high,open,low,close,p_close,p_change,f_high,f_low,trades,quantity,amount,buy_o,buy_q,sell_o,sell_q;

    for(int i=0;i<arr_companies.size();i++){
        date_list.append(date);
//        time_list.append(time);
        QString symbol=arr_companies.at(i)["symbol"].toString();
        symbol_list.append(symbol);
        name_list.append(arr_companies.at(i)["securityName"].toString());
        open.append(arr_companies.at(i)["openPrice"].toDouble());
        high.append(arr_companies.at(i)["highPrice"].toDouble());
        low.append(arr_companies.at(i)["lowPrice"].toDouble());
        close.append(arr_companies.at(i)["closePrice"].toDouble());
        p_close.append(arr_companies.at(i)["previousDayClosePrice"].toDouble());
        double pc=p_close.at(close.size()-1).toDouble();
        p_change.append(QString::number(((close.at(close.size()-1).toDouble()-pc)*100)/pc,'f',2));
        f_high.append(arr_companies.at(i)["fiftyTwoWeekHigh"].toDouble());
        f_low.append(arr_companies.at(i)["fiftyTwoWeekLow"].toDouble());
        trades.append(arr_companies.at(i)["totalTrades"].toInt());
        quantity.append(arr_companies.at(i)["totalTradedQuantity"].toInt());
        amount.append(arr_companies.at(i)["totalTradedValue"].toDouble());
        int d_index=this->get_index(demand,symbol);
        if (d_index!=-1){
            buy_o.append(demand.at(d_index)["totalOrder"].toInt());
            buy_q.append(demand.at(d_index)["totalQuantity"].toInt());
            demand.removeAt(d_index);
        }
        else{
            buy_o.append("");
            buy_q.append("");
        }
        int s_index=this->get_index(supply,symbol);
        if (s_index!=-1){
            sell_o.append(supply.at(s_index)["totalOrder"].toInt());
            sell_q.append(supply.at(s_index)["totalQuantity"].toInt());
            supply.removeAt(s_index);
        }
        else{
            sell_o.append("");
            sell_q.append("");
        }
//        break;

    }

    QSqlQuery qry(this->db2.db);
    qry.prepare("insert into Todays_Price values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    qry.addBindValue(date_list);
//    qry.addBindValue(time_list);
    qry.addBindValue(symbol_list);
    qry.addBindValue(name_list);
    qry.addBindValue(open);
    qry.addBindValue(high);
    qry.addBindValue(low);
    qry.addBindValue(close);
    qry.addBindValue(p_close);
    qry.addBindValue(p_change);
    qry.addBindValue(f_high);
    qry.addBindValue(f_low);
    qry.addBindValue(trades);
    qry.addBindValue(quantity);
    qry.addBindValue(amount);
    qry.addBindValue(buy_o);
    qry.addBindValue(buy_q);
    qry.addBindValue(sell_o);
    qry.addBindValue(sell_q);
    return qry.execBatch();

}



bool Html::save_sharesansar(QByteArray text, QString symbol)
{
    QRegExp re("<table class=\"table table-bordered table-striped table-hover text-center company-table\">.+Bonus Share.+</table>");
    re.setMinimal(true);
    int val=re.indexIn(text);

    if (val==-1){
        return false;
    }


    QString table=re.cap(0);

    QRegExp re1("Bonus Share</td>.+<td>(.+)</td>");
    QRegExp re2("Cash Dividend</td>.+<td>(.+)</td>");
    QRegExp re3("Year</td>.+<td>(.+)</td>");
    QRegExp re4("Book Close Date</td>.+<td>(.+)</td>");



    re1.setMinimal(true);
    re2.setMinimal(true);
    re3.setMinimal(true);
    re4.setMinimal(true);


    int pos = re1.indexIn(table);Q_UNUSED(pos);
    int pos2 = re2.indexIn(table);Q_UNUSED(pos2);
    int pos3 = re3.indexIn(table);Q_UNUSED(pos3);
    int pos4 = re4.indexIn(table);Q_UNUSED(pos4);


    QString ts=re1.cap(1);ts=ts.remove('%').simplified();
    QString ts2=re2.cap(1);ts2=ts2.remove('%').simplified();
    QString ts3=re3.cap(1);
    QString ts4=re4.cap(1);

    bool ok,ok2;

    double bonus=ts.toDouble(&ok);
    double dividend=ts2.toDouble(&ok2);

    if (ok==true && ok2==true){
        if(bonus==0 && dividend==0){
            return 0;
        }
        else if (bonus==0 && dividend!=0){
            QSqlQuery qry(this->db.db);
            qry.prepare(QString("update Stock set Dividend=?, Book_Close=? where Symbol='%1'").arg(symbol));

            qry.addBindValue(ts2+" ("+ts3+")");
            qry.addBindValue(ts4);

            return qry.exec();
        }
        else if (bonus!=0 && dividend==0){
            QSqlQuery qry(this->db.db);
            qry.prepare(QString("update Stock set Bonus=?, Book_Close=? where Symbol='%1'").arg(symbol));

            qry.addBindValue(ts+" ("+ts3+")");
            qry.addBindValue(ts4);

            return qry.exec();
        }
        else {
            QSqlQuery qry(this->db.db);
            qry.prepare(QString("update Stock set Bonus=?, Dividend=?, Book_Close=? where Symbol='%1'").arg(symbol));
            qry.addBindValue(ts+" ("+ts3+")");
            qry.addBindValue(ts2+" ("+ts3+")");
            qry.addBindValue(ts4);

            return qry.exec();
        }
    }
    return false;
}

bool Html::save_sharesansar_id(QByteArray text, QString symbol)
{
    QList<QStringList> sector=this->db.to_list(this->db.query_select(QString("select Sector from Stock where Symbol='%1'").arg(symbol)));
    QRegExp re2("<div id=\"companyid\" style=\"display: none;\">(.+)</div>");

    re2.setMinimal(true);

    int pos2 = re2.indexIn(text);Q_UNUSED(pos2);

    if (pos2==-1){
        return false;
    }

    QString ts2=re2.cap(1);

    QSqlQuery qry(this->db3.db);
    qry.prepare("insert into sharesansar_companyid values(?,?,?)");
    qry.addBindValue(symbol);
    qry.addBindValue(sector[0][0]);
    qry.addBindValue(ts2.toInt());
    return qry.exec();

}

bool Html::show_events(QByteArray text, int iden, QString symbol)
{
    text.insert(0,'[');
    text.insert(text.size(),']');
    QJsonParseError parse_error;

    //read and parse from file
    QJsonDocument doc = QJsonDocument::fromJson(text,
                                               &parse_error);

    //check parsing errors
    if (parse_error.error != QJsonParseError::NoError) {
        qDebug() << "Parsing error:" << parse_error.errorString();
        return 1;
    }

    QJsonArray data = doc.array().at(0)["data"].toArray();
    qDebug()<<symbol << text;

    int val=-1;

    if(iden==700){
        QString final_table="<br><br>";
        final_table.append("<h3>"+symbol+"</h3>");
        final_table.append("<table><tbody>");
        for(int j=0;j<data.size();j++){
            final_table.append("<tr>");
            final_table.append("<td>"+data.at(j)["published_date"].toString()+"</td>");
            final_table.append("<td>"+data.at(j)["title"].toString()+"</td>");
            final_table.append("</tr><br>");
        }

        final_table.append("</tbody></table>");
        this->mw->text_news->append(final_table);
        return true;
    }
    else if(iden==70){
        val=-3;
    }
//    qDebug()<<symbol;
    QString y_day=this->date.addDays(val).toString("yyyy-MM-dd");

    int pos=0,count=0;

    for(int i=0;i<data.size();i++){
        QString d=data.at(i)["published_date"].toString();
        pos=i;
        if(d.compare(y_day)<0){
            break;
        }
        count++;
    }
    if (count){
        QString final_table="<br><br>";
        final_table.append("<h3>"+symbol+"</h3>");
        final_table.append("<table><tbody>");
        for(int j=0;j<pos;j++){
            final_table.append("<tr>");
            final_table.append("<td>"+data.at(j)["published_date"].toString()+"</td>");
            final_table.append("<td>"+data.at(j)["title"].toString()+"</td>");
            final_table.append("</tr><br>");
        }

        final_table.append("</tbody></table>");
        this->mw->text_news->append(final_table);
    }



//    qDebug()<<pos<<final_table;
    return true;
}

bool Html::show_reports(QByteArray text, int iden, QString symbol)
{
    text.insert(0,'[');
    text.insert(text.size(),']');
    QJsonParseError parse_error;

    //read and parse from file
    QJsonDocument doc = QJsonDocument::fromJson(text,
                                               &parse_error);

    //check parsing errors
    if (parse_error.error != QJsonParseError::NoError) {
        qDebug() << "Parsing error:" << parse_error.errorString();
        return 1;
    }

    QJsonArray data = doc.array().at(0)["data"].toArray();
//    qDebug()<<symbol << data << text;

    int val=-1;

    if(iden==800){
        QString final_table="<br><br>";
        final_table.append("<h3>"+symbol+"</h3>");
        final_table.append("<table><tbody>");
        for(int j=0;j<data.size();j++){
            final_table.append("<tr>");
            final_table.append("<td>"+data.at(j)["published_date"].toString()+"</td>");
            final_table.append("<td>"+data.at(j)["title"].toString()+"</td>");
            final_table.append("</tr><br>");
        }

        final_table.append("</tbody></table>");
        this->mw->text_reports->append(final_table);
        return true;
    }
    else if(iden==80){
        val=-3;
    }
//    qDebug()<<symbol;
    QString y_day=this->date.addDays(val).toString("yyyy-MM-dd");

    int pos=0,count=0;

    for(int i=0;i<data.size();i++){
        QString d=data.at(i)["published_date"].toString();
        pos=i;
        if(d.compare(y_day)<0){
            break;
        }
        count++;
    }
    if (count){
        QString final_table="<br><br>";
        final_table.append("<h3>"+symbol+"</h3>");
        final_table.append("<table><tbody>");
        for(int j=0;j<pos;j++){
            final_table.append("<tr>");
            final_table.append("<td>"+data.at(j)["published_date"].toString()+"</td>");
            final_table.append("<td>"+data.at(j)["title"].toString()+"</td>");
            final_table.append("</tr><br>");
        }

        final_table.append("</tbody></table>");
        this->mw->text_reports->append(final_table);
    }



//    qDebug()<<pos<<final_table;
    return true;
}

bool Html::save_dividends(QByteArray text, int iden, QString symbol)
{
    text.insert(0,'[');
    text.insert(text.size(),']');
    QJsonParseError parse_error;

    //read and parse from file
    QJsonDocument doc = QJsonDocument::fromJson(text,
                                               &parse_error);

    //check parsing errors
    if (parse_error.error != QJsonParseError::NoError) {
        qDebug() << "Parsing error:" << parse_error.errorString();
        return 1;
    }

    QJsonArray data = doc.array().at(0)["data"].toArray();
//    qDebug()<<symbol << data;


    if(iden==70){
        return true;
    }
//    else if(iden==700){
//        val=-3;
//    }



    QList<QStringList> years=this->db.to_list(this->db.query_select(QString("select year from Insurance_Data where symbol='%1' order by year asc").arg(symbol)));
    int b_year=years[0][0].toInt();

    QSqlQuery qry(this->db.db);
    qry.prepare(QString("update insurance_data set bonus=?,dividend=? where symbol='%1' and year=? and quarter=4").arg(symbol));
    QStringList bonuses,dividends;
    QVariantList yrs;
    QString bonus,dividend;
    for(int i=0;i<data.size();i++){
        int year=data.at(i)["year"].toString().mid(2,2).toInt();
//        qDebug()<<year<<b_year;
        if(year<b_year){
            break;
        }
        bonus=data.at(i)["bonus_share"].toString();
        if(bonus.isEmpty()==true){
            bonus="0.00";
        }
        dividend=data.at(i)["cash_dividend"].toString();
        if(dividend.isEmpty()==true){
            dividend="0.00";
        }
        bonuses<<bonus;
        dividends<<dividend;
        yrs<<year;

    }
    if(bonuses.size()==0){
        return false;
    }
//    qDebug()<<bonuses<<dividends;
    qry.addBindValue(bonuses);
    qry.addBindValue(dividends);
    qry.addBindValue(yrs);
    return qry.execBatch();
}

bool Html::save_demand_supply(QByteArray text)
{
    text.insert(0,'[');
    text.insert(text.size(),']');

    QJsonParseError parse_error;

    //read and parse from file
    QJsonDocument doc = QJsonDocument::fromJson(text,
                                               &parse_error);

    //check parsing errors
    if (parse_error.error != QJsonParseError::NoError) {
        qDebug() << "Parsing error:" << parse_error.errorString();
        return 1;
    }


    QJsonArray demand = doc.array().at(0)["demandList"].toArray();
    QJsonArray supply = doc.array().at(0)["supplyList"].toArray();

//    qDebug()<<"Demand";
//    qDebug()<<demand<<supply;

//    for(int i=0;i<demand.size();i++){
//        QString symbol=demand.at(i)["symbol"].toString();
//        qDebug()<<symbol;
//        QSqlQuery qry(this->db.db);
//        qry.prepare("update Stock set Buy_Orders=?, Buy_Quantity=? where Symbol=?");
//        qry.addBindValue(demand.at(i)["totalOrder"].toInt());
//        qry.addBindValue(demand.at(i)["totalQuantity"].toInt());
//        qry.addBindValue(demand.at(i)["symbol"].toString());
//        qDebug()<<qry.exec();

//    }

//    qDebug()<<"Supply";

//    for(int i=0;i<supply.size();i++){
//        QSqlQuery qry(this->db.db);
//        qry.prepare("update Stock set Sell_Orders=?, Sell_Quantity=? where Symbol=?");
//        qry.addBindValue(supply.at(i)["totalOrder"].toInt());
//        qry.addBindValue(supply.at(i)["totalQuantity"].toInt());
//        qry.addBindValue(supply.at(i)["symbol"].toString());
//        qDebug()<<qry.exec();

//    }

//    qDebug()<<"Finished";
//    return true;

    QVariantList B_O,B_Q,S_O,S_Q;
    QStringList B_S,S_S;

    for(int i=0;i<demand.size();i++){
        B_O.append(demand.at(i)["totalOrder"].toInt());
        B_Q.append(demand.at(i)["totalQuantity"].toInt());
        B_S.append(demand.at(i)["symbol"].toString());
    }

    for(int i=0;i<supply.size();i++){
        S_O.append(supply.at(i)["totalOrder"].toInt());
        S_Q.append(supply.at(i)["totalQuantity"].toInt());
        S_S.append(supply.at(i)["symbol"].toString());

    }

    qDebug()<<B_O.size()<<B_Q.size()<<B_S.size()<<S_O.size()<<S_Q.size()<<S_S.size();

    bool demand_check,supply_check;

    QSqlQuery qry(this->db.db);
    qry.prepare("update Stock set Buy_Orders=?, Buy_Quantity=? where Symbol=?");
    qry.addBindValue(B_O);
    qry.addBindValue(B_Q);
    qry.addBindValue(B_S);
    demand_check=qry.execBatch();

    QSqlQuery qry2(this->db.db);
    qry2.prepare("update Stock set Sell_Orders=?, Sell_Quantity=? where Symbol=?");
    qry2.addBindValue(S_O);
    qry2.addBindValue(S_Q);
    qry2.addBindValue(S_S);
    supply_check=qry2.execBatch();

    return supply_check & demand_check;
}

int Html::get_index(QJsonArray companies, QString symbol){
    for(int i=0;i<companies.size();i++){
        if(companies.at(i)["symbol"].toString()==symbol){
            return i;
        }
    }
    return -1;
}


QString Html::get_table(QString text,int index)
{
    QString table;
    QRegExp re1("(<table)");
    QRegExp re2("(</table>)");
    re1.setMinimal(true);
    re2.setMinimal(true);
    int count=0,pos=0,pos2=0,pos3=0;
    while((pos=re1.indexIn(text,pos))!=-1){
        pos2=re2.indexIn(text,pos);
        pos3=re1.indexIn(text,pos);
        while(pos3<pos2 && pos3!=-1){
            table=text.mid(pos3,(pos2+8-pos3));
            pos3=re1.indexIn(text,pos3+1);

        }
        count++;
        pos=pos2;
        if(count==index){
            return table;
        }
    }
    return "";
}


QList<QStringList> Html::parse_table(QString table)
{
    Table_parser *tp=new Table_parser();
    tp->init(table);
    return tp->tablelist;
}

QList<QList<QStringList>> Html::special_parse_table(QString table)
{
    Special_table_parser *tpp=new Special_table_parser();
    tpp->init(table);
    return tpp->tablelist;
}

QList<QList<QStringList>> Html::super_special_parser_table(QString table)
{
    Super_special_table_parser *tpp=new Super_special_table_parser();
    tpp->init(table);
    return tpp->tablelist;
}


QList<QStringList> Html::beautify_table_parsed(QList<QStringList> table)
{
    QList<QStringList> rtable;

    for(int i=0;i<table.length();i++){
        QStringList a=table.at(i);
        QStringList rtr;

        for(int j=0;j<a.length();j++){
            QString b=a.at(j);
            b.replace("&nbsp;"," ");
            QString c=b.simplified();

            rtr<<c;
        }
        rtable<<rtr;
    }
    return rtable;
}


QList<QList<QStringList>> Html::beautify_special_table_parsed(QList<QList<QStringList>> table)
{
    QList<QList<QStringList>> rtable;

    for(int i=0;i<table.length();i++){
        QList<QStringList> a=table.at(i);
        QList<QStringList> rtr;

        for(int j=0;j<a.length();j++){
            QStringList b=a.at(j);
            QStringList rtd;

            for(int k=0;k<b.length();k++){
                QString c=b.at(k);
                c.replace("&nbsp;","");
                QString rdata=c.simplified();
                rtd<<rdata;
            }
            rtr<<rtd;
        }
        rtable<<rtr;
    }
    return rtable;
}


