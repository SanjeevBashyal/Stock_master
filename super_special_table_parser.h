#ifndef TODAYS_PRICE_TABLE_PARSER_H
#define TODAYS_PRICE_TABLE_PARSER_H

#include<QString>
#include<QChar>
#include<QStringList>
#include<QRegExp>

class Super_special_table_parser
{
public:
    QString strtag;
    QString strctag;
    QString strtagcontent;
    QString singletags[3]={"<br>","<input>","<img>"};
    QStringList data;
    QList<QStringList> tdlist;
    QList<QList<QStringList>> tablelist;
    QRegExp rx;

    int counter=0;
    int k=0;
    int flag=0;
    int closure[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int td=-1;
    int tr=-1;
    int pos[15][2]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};



public:
    Super_special_table_parser();
    void init(QString);
    void run(QString);
    int tagcheck();
    void adjuster(QString str,int c, int d);
    void runner(int);

};



#endif // TODAYS_PRICE_TABLE_PARSER_H
