#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_text.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    this->ui->text_news->setOpenExternalLinks(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::set_req_ui(Ui::MainWindow * win)
{
    this->ns.rq.mw=win;
    this->ns.rq.htm.mw=win;
    return true;
}

bool MainWindow::defaults()
{
    this->ui->table_reports->setColumnCount(4);
//    this->ui->table_reports->setRowCount(1);
    QStringList data;
    data<<"Symbol"<<"Date"<<"Year"<<"Quarter";
    for(int i=0;i<4;i++){
        QTableWidgetItem *item=new QTableWidgetItem(data[i]);
        this->ui->table_reports->setHorizontalHeaderItem(i,item);
    }
    return true;
}


void MainWindow::on_push_sss_clicked()
{
    this->ui->text_update->append("SSS: Running");
    this->ns.snatch_from_sharesansar();
}

void MainWindow::on_push_tp_clicked()
{
    this->ui->text_update->append("TP: Running");
    this->ns.snatch_todays_price();
}

void MainWindow::on_push_ds_clicked()
{
    this->ui->text_update->append("DS: Running");
    this->ns.snatch_demand_supply();
}

void MainWindow::on_push_ml_clicked()
{
    this->ui->text_update->append("ML: Running");
    this->ns.snatch_from_merolagani();
}


void MainWindow::on_push_ns_clicked()
{
    this->ui->text_news->clear();
    this->ui->text_update->append("NS: Running to Finish");
    this->ui->utensils->setCurrentIndex(1);
    this->ns.snatch_events(7);
}

void MainWindow::on_line_news_returnPressed()
{
    this->ui->text_news->clear();
    QString text=this->ui->line_news->text().toUpper();

    if(text==":"){
        this->ns.snatch_events(7);
    }
    else if(text=="::"){
        this->ns.snatch_events(700);
    }
    else if(text==":::"){
        this->ns.snatch_events(70);
    }
    else if(text.isEmpty()==false){
        QList<QStringList> symbols=this->ns.rq.htm.db3.to_list(this->ns.rq.htm.db3.query_select(QString("select id from sharesansar_companyid where symbol='%1'").arg(text)));
        qDebug()<<symbols;
        if(symbols.isEmpty()){
            this->ui->text_news->append("Error");
        }
        else{
            this->ns.rq.get_xhttp(QString("https://www.sharesansar.com/ajaxcompanynews?companyid=%1").arg(symbols[0][0]),50,text);

        }
    }

}

void MainWindow::on_push_qr_clicked()
{
    this->ui->table_reports->clearContents();
    this->ns.snatch_reports(8);
}

void MainWindow::on_push_news_enlarge_clicked()
{
    Dialog_text ts;
    ts.set_text(this->ui->text_news->toHtml());
//    ts.show();
    ts.exec();


}

void MainWindow::on_push_bd_clicked()
{
    this->ui->text_update->append("BD: Running");
    this->ns.snatch_dividends(9);
}

void MainWindow::on_push_ts_clicked()
{
    this->ns.calc_ros(0);
//    this->ns.snatch_stock_price("RBCL","2016-00-15","2016-12-15");
}



void MainWindow::on_push_ss_clicked()
{
    this->ui->text_update->append("SS: Running");
    this->ns.snatch_stocks();
}

void MainWindow::on_push_nse_clicked()
{
    this->ui->text_update->append("NSE: Running");
    this->ns.snatch_stock_shares();
}
