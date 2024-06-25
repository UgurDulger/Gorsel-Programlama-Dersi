#include "dialog.h"
#include "ui_dialog.h"
#include "QMessageBox"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::asal_çarpan_hesapla(){

}

void Dialog::on_pushButton_clicked()
{
    if(ui->spinBox->value() > ui->spinBox_2->value())
    {
        QMessageBox::critical(this,"Hata","Aralıkları Kontrol Ediniz","ok");
        accept();

    }
   int ran = rand() % (ui->spinBox_2->value() - ui->spinBox->value() +1) + ui->spinBox->value();
   ui->label_4->setText("Üretilen Sayi:"+QString::number(ran));
}

void Dialog::on_pushButton_3_clicked()
{
    accept();
}
