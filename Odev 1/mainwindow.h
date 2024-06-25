#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QApplication>
#include <QStyle>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include "balonlar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void sureYaz();
    void balonuret();
    void yerdegistir();
    void patlat();
    void gizle();
    void balontime();



private:
    Ui::MainWindow *ui;

    QList<balon*> balonlar;
    QList<balon*> kuyruktaki_balonlar;
    QList<balon*> silinen_balonlar;
    int uzunluk;
    int genislik;
    QTimer *zaman_sayac;
    QTimer *olusma_sayac;
    QTimer *yazma_sayac;
};
#endif // MAINWINDOW_H
