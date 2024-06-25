#include "balonlar.h"
#include "ui_balonlar.h"

Balonlar::Balonlar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Balonlar)
{
    ui->setupUi(this);
}

Balonlar::~Balonlar()
{
    delete ui;
}
