#include "nepse.h"
#include <QString>
#include<QUrlQuery>
#include "request.h"
#include "sqlite_database.h"

Nepse::Nepse()
{

}

int Nepse::snatch_stocks()
{
    QString url="https://newweb.nepalstock.com/api/nots/company/list";
    this->rq.get(url,1,-1);
    return 0;
}

int Nepse::snatch_stock_shares()
{
    QList<QStringList> ids=this->rq.htm.db.to_list(this->rq.htm.db.query_select("select ID from Stock"));
    QString url="https://newweb.nepalstock.com/api/nots/security/";
    QString qurl;
    for(int i=0;i<ids.size();i++){
        qurl=url+ids[i][0];
        this->rq.get(QUrl(qurl),6,ids[i][0].toInt());
    }
    return 0;
}

int Nepse::snatch_from_merolagani()
{
    QList<QStringList> symbols=this->rq.htm.db.to_list(this->rq.htm.db.query_select("select Symbol from Stock"));
    QString url="https://merolagani.com/CompanyDetail.aspx?symbol=";
    QString qurl;
    for(int i=0;i<symbols.size();i++){
        qurl=url+symbols[i][0];
        qDebug()<<qurl;
        this->rq.get(QUrl(qurl),4,symbols[i][0]);
//        break;
    }
    return 0;
}

int Nepse::snatch_todays_price()
{
    this->rq.flags.clear();
    this->rq.flags<<false<<false;
    this->rq.data.clear();
    this->rq.data<<""<<"";
    QString url1="https://newweb.nepalstock.com/api/nots/nepse-data/today-price?size=500";
    QString url2="https://newweb.nepalstock.com/api/nots/nepse-data/supplydemand?all=true";

    this->rq.get_collect(QUrl(url1),0,3);
    this->rq.get_collect(QUrl(url2),1,3);

    return 0;
}

int Nepse::snatch_from_sharesansar()
{
    QList<QStringList> symbols=this->rq.htm.db.to_list(this->rq.htm.db.query_select("select Symbol from Stock where Type='Equity'"));
    QString url="https://www.sharesansar.com/company/";

    QString qurl;
    for(int i=0;i<symbols.size();i++){
        qurl=url+symbols[i][0];
        qDebug()<<qurl;
        this->rq.get(QUrl(qurl),5,symbols[i][0]);
//        break;
    }
    return 0;
}

int Nepse::snatch_sharesansar_id()
{
    QList<QStringList> symbols=this->rq.htm.db.to_list(this->rq.htm.db.query_select("select Symbol from Stock where Type='Equity'"));
    QString url="https://www.sharesansar.com/company/";

    QString qurl;
    for(int i=0;i<symbols.size();i++){
        qurl=url+symbols[i][0];
        qDebug()<<qurl;
        this->rq.get(QUrl(qurl),11,symbols[i][0]);
//        break;
    }
    return 0;
}

int Nepse::snatch_demand_supply()
{
    QString url="https://newweb.nepalstock.com/api/nots/nepse-data/supplydemand?all=true";
    this->rq.get(QString(url),10,-1);
    return 0;
}

int Nepse::snatch_events(int iden)
{
    QString url="https://www.sharesansar.com/company-news?draw=1&start=0&length=10&company=";
    QList<QStringList> symbols=this->rq.htm.db3.to_list(this->rq.htm.db3.query_select("select symbol,id from sharesansar_companyid"));
    QString qurl;
    for(int i=0;i<symbols.size();i++){
        qurl=url+symbols[i][1];
        qDebug()<<qurl;
        this->rq.get_xhttp(QUrl(qurl),iden,symbols[i][0]);
//        break;
    }
    return 0;
}

int Nepse::snatch_reports(int iden)
{
    QString url="https://www.sharesansar.com/company-announcement-category?draw=1&start=0&length=10&category=financial-analysis&company=";
    QList<QStringList> symbols=this->rq.htm.db3.to_list(this->rq.htm.db3.query_select("select symbol,id from sharesansar_companyid"));
    QString qurl;
    for(int i=0;i<symbols.size();i++){
        qurl=url+symbols[i][1];
        qDebug()<<qurl;
        this->rq.get_xhttp(QUrl(qurl),iden,symbols[i][0]);
//        break;
    }
    return 0;
}

int Nepse::snatch_dividends(int iden)
{
    QString url="https://www.sharesansar.com/company-dividend?draw=1&start=0&length=10&company=";
    QList<QStringList> symbols=this->rq.htm.db3.to_list(this->rq.htm.db3.query_select("select symbol,id from sharesansar_companyid where Sector in ('Life Insurance','Non Life Insurance')"));

    QString qurl;
    for(int i=0;i<symbols.size();i++){
        qurl=url+symbols[i][1];
        qDebug()<<qurl;
        this->rq.get_xhttp(QUrl(qurl),iden,symbols[i][0]);
//        break;
    }
    return 0;
}

int Nepse::snatch_stock_price(QString symbol,QString start,QString end)
{
    QString url="https://merolagani.com/handlers/webrequesthandler.ashx";
    QStringList ids,values;
    ids<<"type"<<"symbol"<<"rangeStartDate"<<"rangeEndDate"<<"resolution";

    QDate s_date=QDate::fromString(start,"yyyy-MM-dd");
    QDateTime s_dt=s_date.startOfDay();
    QDate e_date=QDate::fromString(end,"yyyy-MM-dd");
    QDateTime e_dt=e_date.endOfDay();

    int s=s_dt.toSecsSinceEpoch();
    int e=e_dt.toSecsSinceEpoch();

    values<<"get_advanced_chart"<<symbol<<QString::number(s)<<QString::number(e)<<"D";
    QByteArray text=this->rq.get_wait(QUrl(url),ids,values);
    qDebug()<<text;
    return 0;

}

int Nepse::calc_roe(int iden)
{
    Q_UNUSED(iden);
    QList<QStringList> symbols=this->rq.htm.db.to_list(this->rq.htm.db.query_select("select distinct Symbol from Insurance_data"));
    for(int i=0;i<symbols.size();i++){
        QList<QStringList> data=this->add_zero(this->rq.htm.db.to_list(this->rq.htm.db.query_select(QString("select Year,Share_Capital,Reserves_and_Surplus,Bonus,Dividend from Insurance_data where quarter=4 and symbol='%1' order by year asc").arg(symbols[i][0]))));
        QVariantList years,roes;
        double net_worth,total_dividend,bonus,dividend,adjusted_net_worth,p_value,value;
        double share=1,roe=1;
        value=((data[0][1].toDouble()+data[0][2].toDouble())*100)/data[0][1].toDouble();
        for(int j=0;j<data.size();j++){
            years<<data[j][0];
            net_worth=((data[j][1].toDouble()+data[j][2].toDouble())*100)/data[j][1].toDouble();
            p_value=value;
            value=share*net_worth;
            roe=value/p_value;
            roes<<QString::number(roe,'f',2);
            bonus=data[j][3].toDouble();
            dividend=data[j][4].toDouble();
            total_dividend=bonus+dividend;
            adjusted_net_worth=net_worth-total_dividend;
            share=share*(1+bonus/100+dividend/adjusted_net_worth);
        }
        QSqlQuery qry(this->rq.htm.db.db);
        qry.prepare(QString("update insurance_data set roe=? where quarter=4 and year=? and symbol='%1'").arg(symbols[i][0]));
        qry.addBindValue(roes);
        qry.addBindValue(years);
        qDebug()<<qry.execBatch();
//        break;
    }
    return 0;

}

int Nepse::calc_ros(int iden)
{
    Q_UNUSED(iden);
    QList<QStringList> symbols=this->rq.htm.db.to_list(this->rq.htm.db.query_select("select distinct Symbol from Insurance_data"));
    for(int i=0;i<symbols.size();i++){
        QList<QStringList> data=this->add_zero(this->rq.htm.db.to_list(this->rq.htm.db.query_select(QString("select Year,Share_Capital,EPS,Past_PE,Bonus,Dividend from Insurance_data where quarter=4 and symbol='%1' order by year asc").arg(symbols[i][0]))));
        QVariantList years,ross;
        double eps,pe,price,total_dividend,bonus,dividend,adjusted_price,p_value,value;
        double share=1,ros=1;
        int start=-1;
        for(int j=0;j<data.size();j++){
            pe=data[j][3].toDouble();
            if(pe==0){
                continue;
            }else{
                start=j;
                break;
            }
        }
        if(start==-1){
            continue;
        }
        value=data[start][2].toDouble()*data[start][3].toDouble();
        for(int j=start;j<data.size();j++){
            eps=data[j][2].toDouble();
            pe=data[j][3].toDouble();
            price=eps*pe;
            years<<data[j][0];
            p_value=value;
            value=share*price;
            ros=value/p_value;
            ross<<QString::number(ros,'f',2);
            bonus=data[j][4].toDouble();
            dividend=data[j][5].toDouble();
            total_dividend=bonus+dividend;
            adjusted_price=price/(1+total_dividend/100);
            share=share*(1+bonus/100+dividend/adjusted_price);
        }
        QSqlQuery qry(this->rq.htm.db.db);
        qry.prepare(QString("update insurance_data set ros=? where quarter=4 and year=? and symbol='%1'").arg(symbols[i][0]));
        qry.addBindValue(ross);
        qry.addBindValue(years);
        qDebug()<<qry.execBatch();
//        break;
    }
    return 0;

}

QList<QStringList> Nepse::add_zero(QList<QStringList> data)
{
    QList<QStringList> out;
    for(int i=0;i<data.size();i++){
        QStringList ls;
        for(int j=0;j<data[i].size();j++){
            if (data[i][j].isEmpty()==true){
                ls<<"0";
            }
            else{
                ls<<data[i][j];
            }
        }
        out<<ls;
    }
    return out;
}



