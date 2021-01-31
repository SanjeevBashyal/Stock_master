#include "request.h"
#include "html.h"
#include <QDebug>
#include <QEventLoop>
#include <QFile>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QtNetwork/QNetworkReply>

Request::Request()
    :db("C:\\Users\\SANJEEV BASHYAL\\Desktop\\NEPSE\\NEPSE_\\Others.db","temp")
{

}

bool Request::ask(QList<QStringList> symbols){

    Q_UNUSED(symbols);

    return true;

}

bool Request::get(QUrl url)
{
    QNetworkAccessManager *ps=new QNetworkAccessManager();
    connect(ps, &QNetworkAccessManager::finished, this, &Request::on_finished);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    ps->get(req);
    return true;
}

bool Request::get(QUrl url,int iden)
{
    QNetworkAccessManager *ps=new QNetworkAccessManager();
    connect(ps, &QNetworkAccessManager::finished, this, &Request::on_finished);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply* reply=ps->get(req);
    reply->setProperty("iden",iden);

    return true;
}

bool Request::get_collect(QUrl url,int pos, int iden)
{
    QNetworkAccessManager *ps=new QNetworkAccessManager();
    connect(ps, &QNetworkAccessManager::finished, this, &Request::on_finished_collect);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply* reply=ps->get(req);
    ps->setTransferTimeout(45000);

    reply->setProperty("position",pos);
    reply->setProperty("iden",iden);


    return true;
}

bool Request::get_syn_sharesansar(QUrl url1, QString symbol, QString sector)
{
    QNetworkAccessManager *ps=new QNetworkAccessManager();

    QNetworkRequest req(url1);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply* reply=ps->get(req);
    ps->setTransferTimeout(45000);

    QEventLoop loop;
    connect(ps, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();

    disconnect(ps, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);




    QByteArray bts = reply->readAll();
    QRegExp re2("<div id=\"companyid\" style=\"display: none;\">(.+)</div>");

    re2.setMinimal(true);

    int pos2 = re2.indexIn(bts);Q_UNUSED(pos2);

//    QString ts=re.cap(1);
    QString ts2=re2.cap(1);

    QSqlQuery qry(this->db.db);
    qry.prepare("insert into sharesansar_companyid values(?,?,?)");
    qry.addBindValue(symbol);
    qry.addBindValue(sector);
    qry.addBindValue(ts2.toInt());
    qDebug()<<qry.exec();

/*

    QNetworkRequest req2(url2);
//    req2.setHeader(QNetworkRequest::ContentTypeHeader, "text/html; charset=UTF-8");
//    req2.setRawHeader("Accept", "");
//    req2.setRawHeader("Accept-Encoding", "gzip, deflate, br");
//    req2.setRawHeader("Accept-Language", "en-US,en;q=0.9");
//    req2.setRawHeader("Connection", "keep-alive");
//    req2.setRawHeader("Cookie", "_ga=GA1.2.1992680831.1601832245; __gads=ID=b0da54622354a879-2280daa468c40045:T=1603766522:RT=1603766522:S=ALNI_MYmLuxVbKe8g2pH6wrLKgs58wkD8g; __cfduid=dadacee1f8066ea9d244f86c5ecc8fc0c1605532389; "+xsrf+session);
//    req2.setRawHeader("Host", "www.sharesansar.com");
//    req2.setRawHeader("Referer", "https://www.sharesansar.com/company/nica");
//    req2.setRawHeader("Sec-Fetch-Dest", "empty");
//    req2.setRawHeader("Sec-Fetch-Mode", "cors");
//    req2.setRawHeader("Sec-Fetch-Site", "same-origin");
//    req2.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.183 Safari/537.36 OPR/72.0.3815.320");
    req2.setRawHeader("X-Requested-With", "XMLHttpRequest");


//    qDebug()<<cookie->setCookiesFromUrl(cookies,url2);
//    ps->setCookieJar(cookie);

    QNetworkReply* reply2=ps->get(req2);

    QEventLoop loop2;
    connect(ps, &QNetworkAccessManager::finished, &loop2, &QEventLoop::quit);
    loop2.exec();

    QByteArray bts2 = reply2->readAll();
    qDebug()<<QString(bts2);
    this->mw->text_news->append(QString(bts2));

    */
    return true;


}

bool Request::get(QUrl url,int iden, int id)
{
    QNetworkAccessManager *ps=new QNetworkAccessManager();
    connect(ps, &QNetworkAccessManager::finished, this, &Request::on_finished);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply* reply=ps->get(req);
    reply->setProperty("iden",iden);
    reply->setProperty("id",id);

    return true;
}

bool Request::get(QUrl url, int iden, QString id)
{
    QNetworkAccessManager *ps=new QNetworkAccessManager();
    connect(ps, &QNetworkAccessManager::finished, this, &Request::on_finished);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply* reply=ps->get(req);
    reply->setProperty("iden",iden);
    reply->setProperty("id",id);

    return true;
}

bool Request::get_xhttp(QUrl url, int iden, QString id)
{
    QNetworkAccessManager *ps=new QNetworkAccessManager();
    connect(ps, &QNetworkAccessManager::finished, this, &Request::on_finished);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setRawHeader("X-Requested-With", "XMLHttpRequest");

    QNetworkReply* reply=ps->get(req);
    reply->setProperty("iden",iden);
    reply->setProperty("id",id);

    return true;
}

//bool Request::get_file(QUrl url, QString symbol, int quarter, int year)
//{
//    QNetworkAccessManager *ps=new QNetworkAccessManager();
//    connect(ps, &QNetworkAccessManager::finished, &Request::on_finished);

//    QNetworkRequest req(url);
//}

bool Request::get_query(QUrl url, QStringList ids, QStringList values, int iden, QString id)
{
    QNetworkAccessManager *ps=new QNetworkAccessManager();
    connect(ps, &QNetworkAccessManager::finished, this, &Request::on_finished);


    QUrlQuery params;
    for (int i = 0; i < ids.size(); ++i)
        params.addQueryItem(ids[i], values[i]);

    QString postData=params.query();
    QUrl qurl=QUrl(url.toString()+postData);

    QNetworkRequest req(qurl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
    req.setRawHeader("X-Requested-With", "XMLHttpRequest");


//    qDebug()<<postData;
    QNetworkReply* reply=ps->get(req);
    reply->setProperty("iden",iden);
    reply->setProperty("id",id);

    return true;
}

QByteArray Request::get_wait(QUrl url, QStringList ids, QStringList values)
{
    QNetworkAccessManager *ps=new QNetworkAccessManager();

    QUrlQuery params;
    for (int i = 0; i < ids.size(); ++i)
        params.addQueryItem(ids[i], values[i]);

    QString postData=params.query();
    QUrl qurl=QUrl(url.toString()+"?"+postData);

    QNetworkRequest req(qurl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setRawHeader("X-Requested-With", "XMLHttpRequest");

    QNetworkReply* reply=ps->get(req);

    QEventLoop loop;
    connect(ps, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();

    disconnect(ps, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    QByteArray bts = reply->readAll();
    return bts;
}

bool Request::post(QUrl url, QStringList ids, QStringList values, int iden, QString id)
{
    QNetworkAccessManager *ps=new QNetworkAccessManager();
    connect(ps, &QNetworkAccessManager::finished, this, &Request::on_finished);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
    req.setRawHeader("X-Requested-With", "XMLHttpRequest");

    QUrlQuery params;
    for (int i = 0; i < ids.size(); ++i)
        params.addQueryItem(ids[i], values[i]);

    QByteArray postData=params.query().toUtf8();

//    qDebug()<<postData;
    QNetworkReply* reply=ps->post(req, postData);
    reply->setProperty("iden",iden);
    reply->setProperty("id",id);

    return true;
}

bool Request::post_json(QUrl url, QStringList ids, QStringList values, int iden, QString id)
{
    QNetworkAccessManager *ps=new QNetworkAccessManager();
    connect(ps, &QNetworkAccessManager::finished, this, &Request::on_finished);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
//    req.setRawHeader("X-Requested-With", "XMLHttpRequest");

    QJsonObject json;
    for(int i=0;i<ids.size();i++){
        json.insert(ids[i],values[i]);
    }
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();
    QNetworkReply* reply=ps->post(req, jsonData);
    reply->setProperty("iden",iden);
    reply->setProperty("id",id);
    return true;
}

void Request::on_finished(QNetworkReply *req)
{
    QVariant redirectionSignal = req->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if(redirectionSignal.toInt()==302) {
        QVariant redirectionTargetUrl = req->attribute(QNetworkRequest::RedirectionTargetAttribute);
        QNetworkAccessManager *ps=new QNetworkAccessManager();
        connect(ps, &QNetworkAccessManager::finished, this, &Request::on_finished);
        QUrl newUrl = QUrl(redirectionTargetUrl.toUrl());
        ps->get(QNetworkRequest(newUrl));
        qDebug()<<newUrl;
    }
    else
    {
        QByteArray bts = req->readAll();

        QVariant qiden = req->property("iden");
        int iden=-1;
        if(qiden.isValid()){
            iden=qiden.toInt();
        }

        QVariant qid = req->property("id");
        if(qid.isValid()){
            if(qid.type()==QVariant::Int){
                int id=qid.toInt();
                bool result=this->htm.get_and_save(bts,iden,id);
//                this->mw->text_update->append(QString(bts));
                this->mw->text_update->append(QString::number(iden)+": "+QVariant(result).toString());
            }
            else if(qid.type()==QVariant::String){
                QString id=qid.toString();
                bool result=this->htm.get_and_save(bts,iden,id);
                this->mw->text_update->append(QString::number(iden)+": "+QVariant(result).toString());
            }
        }
        else {
            bool result=this->htm.get_and_save(bts,iden,-1);
            this->mw->text_update->append(QString::number(iden)+": "+QVariant(result).toString());
        }

    }
}

void Request::on_finished_collect(QNetworkReply *req)
{
    QVariant redirectionSignal = req->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QVariant qpos = req->property("position");
    int pos;
    if(qpos.isValid()){
        pos=qpos.toInt();
    }

    if(redirectionSignal.toInt()==302) {
        QVariant redirectionTargetUrl = req->attribute(QNetworkRequest::RedirectionTargetAttribute);
        QNetworkAccessManager *ps=new QNetworkAccessManager();
        connect(ps, &QNetworkAccessManager::finished, this, &Request::on_finished_collect);
        QUrl newUrl = QUrl(redirectionTargetUrl.toUrl());
        ps->get(QNetworkRequest(newUrl));
        qDebug()<<newUrl;
    }
    else
    {
        QByteArray bts = req->readAll();
        this->flags[pos]=true;
        this->data[pos]=bts;

        bool result=true;
        for(int i=0; i<this->flags.size(); i++){
            result = result & this->flags[i];
        }
        if(result==true){
            QVariant qiden = req->property("iden");
            int iden=-1;
            if(qiden.isValid()){
                iden=qiden.toInt();
            }
            this->run_this(iden,this->flags.size());
        }
    }
}

void Request::downloaded(QNetworkReply *req)
{
    QByteArray bts = req->readAll();
    QFile f("C:\\Users\\SANJEEV BASHYAL\\Desktop\\NEPSE\\Quarterly_Reports\\Not Done");

}

bool Request::run_this(int iden,int size){
    bool result=this->htm.get_and_save(this->data,iden,size);
    this->mw->text_update->append(QString::number(iden)+": "+QVariant(result).toString());
    return result;
}
