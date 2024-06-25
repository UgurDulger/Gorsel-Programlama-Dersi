#include "dersislemleri.h"
#include "ui_dersislemleri.h"

dersislemleri::dersislemleri(QSqlDatabase veritabani,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dersislemleri)
{
    ui->setupUi(this);
    veritabanisorgusu=new QSqlQuery(veritabani);
    yazdir();
}

dersislemleri::~dersislemleri()
{
    delete ui;
}
void dersislemleri::yazdir()
{
    veritabanisorgusu->prepare("select * from dersler");
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }

    mod=new QSqlQueryModel();
    mod->setQuery(*veritabanisorgusu);
    ui->tw_tumdersler->setModel(mod);

}

void dersislemleri::on_tw_tumdersler_clicked(const QModelIndex &index)
{
    ui->lineE_Kod->setText(mod->index(index.row(),0).data().toString());
    ui->lineE_Ad->setText(mod->index(index.row(),1).data().toString());

    QString indis = mod->index(index.row(),0).data().toString();
    int dep_id = indis.toInt();

    QSqlQuery sorgu;

    sorgu.prepare("select * from notlar WHERE Ders_Kodu= ?");
    sorgu.addBindValue(dep_id);
    sorgu.exec();
    mod_ogr = new QSqlQueryModel();
    mod_ogr->setQuery(sorgu);
    ui->tw_secilendersler->setModel(mod_ogr);

}


void dersislemleri::on_pb_kayit_clicked()
{
    if(ui->lineE_Ad->text() == "" || ui->lineE_Kod->text() == "" )
    {
        QMessageBox::critical(this,"Ders Ekleme Hatası","Girilen alanlarda boş yer bırakmayınız","Tamam");
        return;
    }
    veritabanisorgusu->prepare("select * from notlar where Ders_Kodu = ?");
    veritabanisorgusu->addBindValue(ui->lineE_Kod->text().toInt());
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }
    int verivarmi = 0;
    while(veritabanisorgusu->next())
    {
     verivarmi++;
    }
    if(verivarmi>0)
    {
        QMessageBox::critical(this,"Uyarı","Bu Kodda Başka Bir Ders Vardır!\n !Eklenemez!","Tamam");
    }
    else{
    veritabanisorgusu->prepare("insert into dersler(Ders_Kodu,Ders_Adı) values(?,?)");
    veritabanisorgusu->addBindValue(ui->lineE_Kod->text().toInt());
    veritabanisorgusu->addBindValue(ui->lineE_Ad->text());
    if(!veritabanisorgusu->exec()){
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
    }
    yazdir();
    }
}

void dersislemleri::on_pb_guncelle_clicked()
{

    if(ui->lineE_Kod->text() == "" || ui->lineE_Ad->text() == "" ){
        QMessageBox::critical(this,"Ders Güncelleme Hatası","Girilen alanlarda boş yer bırakmayınız","Tamam");
        return;
    }
    veritabanisorgusu->prepare("update dersler set Ders_Kodu=?,Ders_Adı=? where Ders_Kodu=?");
    veritabanisorgusu->addBindValue(ui->lineE_Kod->text());
    veritabanisorgusu->addBindValue(ui->lineE_Ad->text());
    veritabanisorgusu->addBindValue(ui->lineE_Kod->text().toInt());

    if(!veritabanisorgusu->exec()){
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
    }
    yazdir();
}

void dersislemleri::on_pb_sil_clicked()
{

    veritabanisorgusu->prepare("select * from notlar where Ders_Kodu = ?");
    veritabanisorgusu->addBindValue(ui->lineE_Kod->text().toInt());
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }
    int verivarmi = 0;
    while(veritabanisorgusu->next())
    {
     verivarmi++;
    }
    if(verivarmi>0)
    {
        QMessageBox::critical(this,"Uyarı","Bu Dersin Öğrencisi Bulunmaktadır!\n !Silinemez!","Tamam");
    }
    else
    {
        veritabanisorgusu->prepare("delete from dersler  where Ders_Kodu = ?");
        veritabanisorgusu->addBindValue(ui->lineE_Kod->text().toInt());

        if(!veritabanisorgusu->exec())
            {
                QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"ok");
                return;
            }
            yazdir();
    }
}
