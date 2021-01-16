#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QVector>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include "ui_mainwindow.h"
#include "html.h"

class Request : public QObject
{
    Q_OBJECT;

public:
    Database db;
public:
    Html htm;
    int count;
    QList<bool> flags;
    QList<QByteArray> data;
public:
    Request();
    bool ask(QList<QStringList>);
    bool get(QUrl);
    bool get(QUrl, int);
    bool get_collect(QUrl, int, int);
    bool get_syn_sharesansar(QUrl, QUrl);
//    bool get_post(QUrl, QUrl);
    bool get(QUrl, int, int);
    bool get(QUrl, int, QString);
    bool get_xhttp(QUrl, int, QString);
    static bool get_file(QUrl, QString, int, int);
    bool get_query(QUrl,QStringList, QStringList, int, QString);
    QByteArray get_wait(QUrl,QStringList,QStringList);
    bool post(QUrl,QStringList, QStringList, int, QString);
    bool post_json(QUrl,QStringList, QStringList, int, QString);
    bool run_this(int,int);

public slots:
    void on_finished(QNetworkReply *);
    void on_finished_collect(QNetworkReply *);
    void downloaded(QNetworkReply *);

public:
    Ui::MainWindow *mw=nullptr;

};

#endif // REQUEST_H