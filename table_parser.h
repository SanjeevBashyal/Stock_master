#ifndef TABLE_PARSER_H
#define TABLE_PARSER_H

#include<QString>
#include<QChar>
#include<QStringList>
#include<QRegExp>

class Table_parser
{
public:
    QString strtag;
    QString strctag;
    QString strtagcontent;
    QString singletags[3]={"<br>","<input>","<img>"};
    QString data;
    QStringList tdlist;
    QList<QStringList> tablelist;
    QRegExp rx;

    int counter=0;
    int k=0;
    int flag=0;
    int closure[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int td=-1;
    int tr=-1;
    int pos[15][2]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};



public:
    Table_parser();
    void init(QString);
    void run(QString);
    int tagcheck();
    void adjuster(QString str,int c, int d);
    void runner(int);

};



#endif // TABLE_PARSER_H
