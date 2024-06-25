#ifndef NOTISLEMLERI_H
#define NOTISLEMLERI_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>


namespace Ui {
class notislemleri;
}

class notislemleri : public QDialog
{
    Q_OBJECT

public:
    explicit notislemleri(QSqlDatabase,QWidget *parent = nullptr);
    ~notislemleri();
    void yazdir();
    void ogrenciyazdir();
    void dersyazdir();
    void hepsiyazdir();


private slots:
    void on_tw_tumogrenciler_clicked(const QModelIndex &index);

    void on_tw_tumdersler_clicked(const QModelIndex &index);

    void on_pb_kayitekle_clicked();

private:
    Ui::notislemleri *ui;
    QSqlQuery *veritabanisorgusu;
    QSqlQueryModel *mod;
    QSqlQueryModel *mod_ogr;
    QSqlQueryModel *mod_ders;
};

#endif // NOTISLEMLERI_H
