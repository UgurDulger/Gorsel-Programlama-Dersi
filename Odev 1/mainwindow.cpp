#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "balonlar.h"
#include "QRandomGenerator"
#include "QDebug"
#include "mainwindow.h"

//19010011026 uğur DÜLGER
//Tam Ekranda çalıştırınız.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    zaman_sayac = new QTimer(this);
    connect(zaman_sayac, SIGNAL(timeout()), this, SLOT(sureYaz()));
    zaman_sayac->start(1000);

    olusma_sayac = new QTimer(this);
    connect(olusma_sayac,SIGNAL(timeout()),this,SLOT(balonuret()));
    olusma_sayac->start(800);

    yazma_sayac = new QTimer(this);
    connect(yazma_sayac,SIGNAL(timeout()),this,SLOT(balontime()));
    yazma_sayac->start(3000);

   //yazma_sayac = new QTimer(this);
    //connect(yazma_sayac,SIGNAL(timeout()),this,SLOT(yerdegistir()));
    //yazma_sayac->start(200);

    QTimer *timer=new QTimer(this);
    timer->start(50);
    connect(timer,&QTimer::timeout,this,&MainWindow::patlat);

    uzunluk =2000;
    genislik = 2000;

}
int sure = 0;
void MainWindow::sureYaz()
{
    QString format("Sure : <font color='blue'>%1</font>");
    ui->lbl_sure->setText(format.arg(QString::number(sure)));
    sure +=1;
}
void MainWindow::balonuret()
{
    int x =  rand() % 1500;
    int y = 115;
    balon *balonnn = new balon(this);
    balonnn->setGeometry(x,y,50,50);
    balonnn->show();
    balonlar.push_back(balonnn);
    int a=QRandomGenerator::global()->generate()%7;
    QString temp = ":/Kaynak/images/"+QString::number(a)+".jpg";

    balonnn->setIcon(QIcon(temp));
    balonnn->setIconSize(QSize(50,50));
}
void MainWindow::gizle(){

    if(kuyruktaki_balonlar.count()!=0){

        kuyruktaki_balonlar.at(0)->hide();
        delete kuyruktaki_balonlar.at(0);
        kuyruktaki_balonlar.removeAt(0);
    }


}
int kacan = 0;
void MainWindow::balontime()
{   int sayisi = balonlar.size()-1;
    for (int x = 0; x < sayisi; x++){
        kacan = silinen_balonlar.size()+1;
        QString format("Kacanlar : <font color='red'>%1</font>");
        ui->lbl_kacanlar->setText(format.arg(QString::number(kacan)));

        balonlar.at(x)->hide();
        silinen_balonlar.append(balonlar.at(x));
        silinen_balonlar.removeAt(x);
    }

}


void MainWindow::yerdegistir()
{
    int sayisi = balonlar.size()-1;
    for (int x = 0; x < sayisi; x++) {
        if(balonlar[x]->y()< 875) {
            balonlar[x]->setGeometry(balonlar[x]->x(),
                                 balonlar[x]->y() + 30,
                                 balonlar[x]->width(),
                                 balonlar[x]->height());
        }
        else{
            kacan = silinen_balonlar.size()+1;
            QString format("Kacanlar : <font color='red'>%1</font>");
            ui->lbl_kacanlar->setText(format.arg(QString::number(kacan)));

            balonlar.at(x)->hide();
            silinen_balonlar.append(balonlar.at(x));
            silinen_balonlar.removeAt(x);

        }
    }
}
int vurulan = 0;
void MainWindow::patlat()
{
    int i;
    for(i=0;i<balonlar.size();i++){
        if(balonlar[i]->tiklandimi == true){
            vurulan = vurulan+1;
            QString format("Vurulanlar : <font color='green'>%1</font>");
            ui->lbl_vurulanlar->setText(format.arg(QString::number(vurulan)));
            QString temp = ":/Kaynak/images/patlama.jpg";

            balonlar[i]->setIcon(QIcon(temp));
            balonlar[i]->setIconSize(QSize(50,50));

            kuyruktaki_balonlar.append(balonlar.at(i));

            balonlar.removeAt(i);

            QTimer::singleShot(2500, this, SLOT(gizle()));

        }
    }
}




MainWindow::~MainWindow()
{
    delete ui;
}

