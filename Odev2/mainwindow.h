#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ogrenciislemleri_clicked();

    void on_pb_dersislemleri_clicked();

    void on_pb_notislemleri_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase veritabani =QSqlDatabase::addDatabase("QSQLITE");

};
#endif // MAINWINDOW_H
