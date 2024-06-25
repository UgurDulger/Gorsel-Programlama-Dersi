#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

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
    void on_pushButton_clicked();
    void readd();
    void yazdir();
    void yazdir_yazilim();

private:
    Ui::MainWindow *ui;
    QSqlDatabase veritabani =QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery *veritabanisorgusu;
    QSqlQueryModel *mod;
    QSqlQueryModel *mod2;
};
#endif // MAINWINDOW_H
