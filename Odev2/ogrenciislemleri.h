#ifndef OGRENCIISLEMLERI_H
#define OGRENCIISLEMLERI_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>


namespace Ui {
class ogrenciislemleri;
}

class ogrenciislemleri : public QDialog
{
    Q_OBJECT

public:
    explicit ogrenciislemleri(QSqlDatabase,QWidget *parent = nullptr);
    ~ogrenciislemleri();
    void yazdir();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_pb_kayt_clicked();

    void on_pb_sil_clicked();

    void on_pb_guncelle_clicked();

private:
    Ui::ogrenciislemleri *ui;
    QSqlQuery *veritabanisorgusu;
    QSqlQueryModel *mod;
};

#endif // OGRENCIISLEMLERI_H

