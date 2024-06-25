#include "notislemleri.h"
#include "ui_notislemleri.h"

notislemleri::notislemleri(QSqlDatabase veritabani,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notislemleri)
{
    ui->setupUi(this);
    veritabanisorgusu=new QSqlQuery(veritabani);
    dersyazdir();
    ogrenciyazdir();
    hepsiyazdir();
}

notislemleri::~notislemleri()
{
    delete ui;
}
void notislemleri::dersyazdir()
{
    veritabanisorgusu->prepare("select * from dersler");
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }

    mod_ders=new QSqlQueryModel();
    mod_ders->setQuery(*veritabanisorgusu);
    ui->tw_tumdersler->setModel(mod_ders);

}
void notislemleri::ogrenciyazdir()
{
    veritabanisorgusu->prepare("select * from ogrenci");
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }

    mod_ogr=new QSqlQueryModel();
    mod_ogr->setQuery(*veritabanisorgusu);
    ui->tw_tumogrenciler->setModel(mod_ogr);

}
void notislemleri::hepsiyazdir()
{
    veritabanisorgusu->prepare("select * from notlar");
    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }

    mod=new QSqlQueryModel();
    mod->setQuery(*veritabanisorgusu);
    ui->tw_hepsi->setModel(mod);

}



void notislemleri::on_tw_tumogrenciler_clicked(const QModelIndex &index)
{
        ui->lineE_OgrNo->setText(mod_ogr->index(index.row(),0).data().toString());
}

void notislemleri::on_tw_tumdersler_clicked(const QModelIndex &index)
{
    ui->lineE_DersKod->setText(mod_ders->index(index.row(),0).data().toString());
}

void notislemleri::on_pb_kayitekle_clicked()
{
    int Gecme_Notu = (ui->lineE_Vize->text().toInt()*0.4)+(ui->lineE_Final->text().toInt()*0.6);
    if(ui->lineE_DersKod->text() == "" || ui->lineE_Final->text() == "" || ui->lineE_OgrNo->text() == "" || ui->lineE_Vize->text() == ""){
        QMessageBox::information(this,"Hata","Gerekli alanlar doldurulmadi!","Tamam");
        return;
    }
    veritabanisorgusu->prepare("select * from notlar where Ders_Kodu = ?");
    veritabanisorgusu->addBindValue(ui->lineE_DersKod->text().toInt());
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
        QMessageBox::critical(this,"Uyarı","Bu Öğrencinin Bu Derste Kaydı Vardır!\n !Eklenemez!","Tamam");
    }
    else{
    veritabanisorgusu->prepare("insert into notlar(Ogr_No,Ders_Kodu,Vize_Not,Final_Not,Gecme_Not) values(?,?,?,?,?)");
    veritabanisorgusu->addBindValue(ui->lineE_OgrNo->text().toInt());
    veritabanisorgusu->addBindValue(ui->lineE_DersKod->text().toInt());
    veritabanisorgusu->addBindValue(ui->lineE_Vize->text().toInt());
    veritabanisorgusu->addBindValue(ui->lineE_Final->text().toInt());
    veritabanisorgusu->addBindValue(Gecme_Notu);


    if(!veritabanisorgusu->exec())
    {
        QMessageBox::critical(this,"Uyarı",veritabanisorgusu->lastError().text(),"Tamam");
        return;
    }
    hepsiyazdir();

    }
}
