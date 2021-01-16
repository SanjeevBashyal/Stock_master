#include "super_special_table_parser.h"

#include<QDebug>
#include<QElapsedTimer>


Super_special_table_parser::Super_special_table_parser(){
    this->rx.setPattern("[\\d\\S]+");

}

void Super_special_table_parser::init(QString str)
{
    QString slr;
    this->pos[0][1]=str.length();

    QElapsedTimer timer;
    timer.start();

    slr=str.mid(this->pos[this->k][0],this->pos[this->k][1]);
    this->run(slr);

    while(this->k!=0){
        slr=str.mid(this->pos[this->k][0],this->pos[this->k][1]-this->closure[this->k]-(this->pos[this->k][0]));
        this->run(slr);

        if(this->flag==1){
            this->k--;
            this->pos[this->k][0]=this->pos[this->k+1][1];

        }

        if(this->k<this->td){
            this->tdlist << this->data;
            this->data.clear();
            this->td=-1;
        }

        if(this->k<this->tr){
            this->tablelist.append(this->tdlist);
            this->tdlist.clear();
            this->tr=-1;
        }

    }
    qDebug() << "The operation took" << timer.elapsed() << "milliseconds";
}

void Super_special_table_parser::run(QString str1)
{
    this->counter++;
    this->flag=0;

    if(str1.isEmpty()==true){
        this->flag=1;

        return;
    }

    QChar st1='<', st2='>'; int m=0;
    int c=str1.indexOf(st1,0);
    int d=str1.indexOf(st2,c);


    if(c==-1 || d==-1){                         //if no tag is found
        this->strtag="";

        if(this->td!=-1){
            if(this->rx.indexIn(str1,0)!=-1){
                this->data<<str1;

            }
        }
        this->flag=1;
        return;

    }

    this->strtagcontent=str1.mid(c,d-c);


        int km=str1.indexOf(" ",c);                  // tag with attributes
        if(d<km || km==-1)
            m=d;
        if(km<d && km>=0)
            m=km;

        this->strtag=str1.mid(c,m-c);
        this->strtag.append(st2);

//        if(this->strtag[1]=='/'){               // if the tag is closing one
//            if(this->td!=-1){
//                QString sr=str1.mid(p,c);
//                if(this->rx.indexIn(sr,0)!=-1){
//                    this->data<<sr;
//                }
//            }
//            this->flag=1;
//            return;
//        }

        int check=0;                            // if the tag is single tag
        while(check<3){
            int checkval=this->strtag.compare(this->singletags[check]);
            if (checkval==0){
                if(check==2){
                    if(this->td!=-1){
                        QString str9=str1.mid(0,c);
                        if(this->rx.indexIn(str9,0)!=-1){
                            str9=rx.cap(0);
                            str9.replace("&nbsp;","");
                            this->data<<str9;
                        }
                    }
                }

                this->pos[k][0]=this->pos[k][0]+d+1;
                return;
            }
            check++;
        }

        QChar c2a='/';                          // declaring closing tag of double tag
        QString s2a=this->strtag;
        s2a.insert(1,c2a);
        this->strctag=s2a;

        if(str1.count(this->strctag)==0){
            this->pos[k][0]=this->pos[k][0]+d+1;
            return;
        }

        this->adjuster(str1,c,d);
        this->runner(0);


}


void Super_special_table_parser::adjuster(QString str, int c, int d){
    this->k++;
    this->pos[this->k][0]=this->pos[this->k-1][0]+d+1;
    int l=this->strctag.length();
    int kk[10]={0,0,0,0,0,0,0,0,0,0},i=0,a,b;QString str1;
    kk[0]=c;
    QString strt=this->strtag.mid(0,this->strtag.length()-1);
    strt.append(" ");
    //QString strink=str.mid(c,-1);
    do{
        i++;
        kk[i]=str.indexOf(this->strctag,kk[i-1]+1);
        str1=str.mid(c,kk[i]+l-c);

        a=str1.count(strt)+str1.count(this->strtag);
        b=str1.count(this->strctag);

    }while(a!=b);
    this->pos[this->k][1]=kk[i]+this->pos[this->k-1][0]+this->strctag.length();
    this->closure[this->k]=this->strctag.length();
}

void Super_special_table_parser::runner(int v)
{
    if(v==0){
        if(this->strtag.compare("<tr>")==0){
            this->tr=this->k;
//            qDebug()<<"here"<<this->strtag;
        }
        else if(this->strtag.compare("<td>")==0){
            this->td=this->k;
        }
        else if(this->strtag.compare("<th>")==0){
            this->td=this->k;
        }
    }
}

int Super_special_table_parser::tagcheck(){
    return 0;
}
