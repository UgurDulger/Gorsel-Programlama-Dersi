#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ogrenciislemleri.h"
#include "dersislemleri.h"
#include "notislemleri.h"
// 19010011026 uğur Dülger
//Hocam kodu beraber incelemiştik çalışmazsa debug ile run da çalışıyo
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    veritabani.setDatabaseName("C:/Users/Pc/Saved Games/Documents/databases/ogrenciotomasyonu.db");
    if(!veritabani.open())
    {
        ui->statusbar->showMessage("Veri tabanına bağlanılamadı!");
    }
    else
    {
        ui->statusbar->showMessage("Veri tabanına bağlanıldı!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ogrenciislemleri_clicked()
{
    ogrenciislemleri *ogrenciler = new ogrenciislemleri(veritabani);
    ogrenciler->show();
}

void MainWindow::on_pb_dersislemleri_clicked()
{
    dersislemleri *dersler = new dersislemleri(veritabani);
    dersler->show();
}

void MainWindow::on_pb_notislemleri_clicked()
{
    notislemleri *notlar = new notislemleri(veritabani);
    notlar->show();
}
