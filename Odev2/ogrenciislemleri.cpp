#include "ogrenciislemleri.h"
#include "ui_ogrenciislemleri.h"

ogrenciislemleri::ogrenciislemleri(QSqlDatabase veritabani,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ogrenciislemleri)
{
    ui->setupUi(this);
    veritabanisorgusu=new QSqlQuery(veritabani);
    yazdir();
}

ogrenciislemleri::~ogrenciislemleri()
{
    delete ui;
}
void ogrenciislemleri::yazdir()
{
    veritabanisorgusu->prepare("select * from ogrenci");
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }

    mod=new QSqlQueryModel();
    mod->setQuery(*veritabanisorgusu);
    ui->tableView->setModel(mod);

}

void ogrenciislemleri::on_tableView_clicked(const QModelIndex &index)
{
    ui->lineE_No->setText(mod->index(index.row(),0).data().toString());
    ui->lineE_Ad->setText(mod->index(index.row(),1).data().toString());
    ui->lineE_Soyad->setText(mod->index(index.row(),2).data().toString());


}

void ogrenciislemleri::on_pb_kayt_clicked()
{
    if(ui->lineE_Ad->text() == "" || ui->lineE_Soyad->text() == "" )
    {
        QMessageBox::critical(this,"Ogrenci Ekleme Hatası","Girilen alanlarda boş yer bırakmayınız","Tamam");
        return;
    }
    veritabanisorgusu->prepare("insert into ogrenci (Ogr_Ad,Ogr_Soyad) values(?,?)");
    veritabanisorgusu->addBindValue(ui->lineE_Ad->text());
    veritabanisorgusu->addBindValue(ui->lineE_Soyad->text());
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }
    yazdir();
}

void ogrenciislemleri::on_pb_sil_clicked()
{
    veritabanisorgusu->prepare("select * from notlar where Ogr_No = ?");
    veritabanisorgusu->addBindValue(ui->lineE_No->text().toInt());
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Hata",veritabanisorgusu->lastError().text(),"Ok");
        return;
    }
    int verivarmi = 0;
    while(veritabanisorgusu->next())
    {
     verivarmi++;
    }
    if(verivarmi>0)
    {
        QMessageBox::critical(this,"Uyarı","Bu Öğrencinin Dersi Bulunmaktadır!\n !Silinemez!","Tamam");
    }
    else
    {
        veritabanisorgusu->prepare("delete from ogrenci  where Ogr_No = ?");
        veritabanisorgusu->addBindValue(ui->lineE_No->text().toInt());

        if(!veritabanisorgusu->exec())
            {
                QMessageBox::critical(this,"Hata",veritabanisorgusu->lastError().text(),"Ok");
                return;
            }
            yazdir();
    }


}

void ogrenciislemleri::on_pb_guncelle_clicked()
{

    veritabanisorgusu->prepare("update ogrenci set Ogr_Ad = ? , Ogr_Soyad = ? where Ogr_No = ?");
    veritabanisorgusu->addBindValue(ui->lineE_Ad->text());
    veritabanisorgusu->addBindValue(ui->lineE_Soyad->text());
    veritabanisorgusu->addBindValue(ui->lineE_No->text().toInt());
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }
    yazdir();
}
