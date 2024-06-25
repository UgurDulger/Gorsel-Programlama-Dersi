#ifndef DERSISLEMLERI_H
#define DERSISLEMLERI_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>

namespace Ui {
class dersislemleri;
}

class dersislemleri : public QDialog
{
    Q_OBJECT

public:
    explicit dersislemleri(QSqlDatabase,QWidget *parent = nullptr);
    ~dersislemleri();
    void yazdir();



private slots:
    void on_tw_tumdersler_clicked(const QModelIndex &index);

    void on_pb_kayit_clicked();

    void on_pb_guncelle_clicked();

    void on_pb_sil_clicked();

private:
    Ui::dersislemleri *ui;
    QSqlQuery *veritabanisorgusu;
    QSqlQueryModel *mod;
    QSqlQueryModel *mod_ogr;

    QString secili_kod;
    QString secili_ad;
};

#endif // DERSISLEMLERI_H
