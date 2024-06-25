#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    veritabani.setDatabaseName("C:/Users/Pc/Saved Games/Documents/databases/quiz2.db");
     veritabanisorgusu=new QSqlQuery(veritabani);

    if (!veritabani.open())
    {
        ui->statusbar->showMessage("Error, Veri tabanına bağlanılamadı X");
    }

    else{
        ui->statusbar->showMessage("Veri tabanına bağlanıldı!");
    }


    readd();


    yazdir();
    yazdir_yazilim();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{

    if(ui->lineEdit->text()=="" || ui->lineEdit_2->text()=="" || ui->lineEdit_3->text()=="" || ui->lineEdit_4->text()==""){

        QMessageBox messageBox;
        messageBox.critical(0,"HATA!","Gerekli Alanları Doldurunuz!");

        return;
    }

    else if(ui->lineEdit_4->text() =="Bilgisayar"){
        int yas ;
        yas = ui->dateEdit->date().year()-2000;
        veritabanisorgusu->prepare("insert into bilgisayar (ogr_id,ogr_ad,ogr_soyad,ogr_yas,ogr_bolum) values(?,?,?,?,?)");
        veritabanisorgusu->addBindValue(ui->lineEdit->text().toInt());
        veritabanisorgusu->addBindValue(ui->lineEdit_2->text());
        veritabanisorgusu->addBindValue(ui->lineEdit_3->text());
        veritabanisorgusu->addBindValue(yas);
        veritabanisorgusu->addBindValue(ui->lineEdit_4->text());
        veritabanisorgusu->exec();
    }

    else{

        int yas ;
        yas = ui->dateEdit->date().year()-2000;
        veritabanisorgusu->prepare("insert into yazilim (ogr_id,ogr_ad,ogr_soyad,ogr_yas,ogr_bolum) values(?,?,?,?,?)");
        veritabanisorgusu->addBindValue(ui->lineEdit->text().toInt());
        veritabanisorgusu->addBindValue(ui->lineEdit_2->text());
        veritabanisorgusu->addBindValue(ui->lineEdit_3->text());
        veritabanisorgusu->addBindValue(yas);
        veritabanisorgusu->addBindValue(ui->lineEdit_4->text());
        veritabanisorgusu->exec();

    }

    yazdir_yazilim();
    yazdir();
}
void MainWindow::readd(){


    QSqlQuery query;

        QFile file("C:/Users/Pc/Saved Games/Documents/databases/ögrenciler.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            return;
        }

        QTextStream in(&file);
        QString line;

        while (!in.atEnd()) {

            line = in.readLine();

            QStringList temp;
            temp = line.split(" ");

            QString bolum = temp.at(4);

            if(bolum == "Bilgisayar"){

                veritabanisorgusu->prepare("insert into bilgisayar (ogr_id,ogr_ad,ogr_soyad,ogr_yas,ogr_bolum) values(?,?,?,?,?)");
                veritabanisorgusu->addBindValue(temp.at(0).toInt());
                veritabanisorgusu->addBindValue(temp.at(1));
                veritabanisorgusu->addBindValue(temp.at(2));
                veritabanisorgusu->addBindValue(temp.at(3).toInt());
                veritabanisorgusu->addBindValue(temp.at(4));
                veritabanisorgusu->exec();
            }

            else{

                veritabanisorgusu->prepare("insert into yazilim (ogr_id,ogr_ad,ogr_soyad,ogr_yas,ogr_bolum) values(?,?,?,?,?)");
                veritabanisorgusu->addBindValue(temp.at(0).toInt());
                veritabanisorgusu->addBindValue(temp.at(1));
                veritabanisorgusu->addBindValue(temp.at(2));
                veritabanisorgusu->addBindValue(temp.at(3).toInt());
                veritabanisorgusu->addBindValue(temp.at(4));
                veritabanisorgusu->exec();

            }

        }

    }

void MainWindow::yazdir()
{
    veritabanisorgusu->prepare("select * from bilgisayar");
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }

    mod=new QSqlQueryModel();
    mod->setQuery(*veritabanisorgusu);
    ui->tableView->setModel(mod);

}
void MainWindow::yazdir_yazilim()
{
    veritabanisorgusu->prepare("select * from yazilim");
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }

    mod2=new QSqlQueryModel();
    mod2->setQuery(*veritabanisorgusu);
    ui->tableView_2->setModel(mod2);

}






