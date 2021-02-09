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
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json, text/javascript, */*; q=0.01");
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
                this->htm.get_and_save(bts,iden,id);
            }
            else if(qid.type()==QVariant::String){
                QString id=qid.toString();
                this->htm.get_and_save(bts,iden,id);
            }
        }
        else {
            this->htm.get_and_save(bts,iden,-1);
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
    this->htm.get_and_save(this->data,iden,size);
    return true;
}
