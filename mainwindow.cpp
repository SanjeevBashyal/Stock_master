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
    this->ns.mw=win;
    this->ns.rq.htm.mw=win;
    return true;
}

bool MainWindow::defaults()
{
    this->ns.defaults();
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
        this->ns.snatch_events(70);
    }
    else if(text==":::"){
        this->ns.snatch_events(700);
    }
    else if(text.isEmpty()==false){
        QList<QStringList> symbols=this->ns.rq.htm.db3.to_list(this->ns.rq.htm.db3.query_select(QString("select id from sharesansar_companyid where symbol='%1'").arg(text)));
        qDebug()<<symbols;
        if(symbols.isEmpty()){
            this->ui->text_news->append("Error");
        }
        else{
            this->ns.rq.get_xhttp(QString("https://www.sharesansar.com/company-news?draw=1&start=0&length=10&company=%1").arg(symbols[0][0]),700,text);

        }
    }

}

void MainWindow::on_line_reports_returnPressed()
{
    this->ui->text_reports->clear();
    QString text=this->ui->line_reports->text().toUpper();

    if(text==":"){
        this->ns.snatch_reports(8);
    }
    else if(text=="::"){
        this->ns.snatch_reports(80);
    }
    else if(text==":::"){
        this->ns.snatch_reports(800);
    }
    else if(text.isEmpty()==false){
        QList<QStringList> symbols=this->ns.rq.htm.db3.to_list(this->ns.rq.htm.db3.query_select(QString("select id from sharesansar_companyid where symbol='%1'").arg(text)));
        qDebug()<<symbols;
        if(symbols.isEmpty()){
            this->ui->text_reports->append("Error");
        }
        else{
            this->ns.rq.get_xhttp(QString("https://www.sharesansar.com/company-announcement-category?draw=1&start=0&length=10&category=financial-analysis&company=%1").arg(symbols[0][0]),800,text);

        }
    }
}

void MainWindow::on_push_qr_clicked()
{
    this->ui->text_reports->clear();
    this->ns.snatch_reports(8);
}

void MainWindow::on_push_news_enlarge_clicked()
{
    Dialog_text ts;
    ts.set_text(this->ui->text_news->toHtml());
//    ts.show();
    ts.exec();


}

void MainWindow::on_push_reports_enlarge_clicked()
{
    Dialog_text ts;
    ts.set_text(this->ui->text_reports->toHtml());
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
//    this->ns.snatch_sharesansar_id();
    this->ns.snatch_quarterly_reports_all("Hotels");
//    this->ns.add_stocks_to_quarterly_reports();

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
