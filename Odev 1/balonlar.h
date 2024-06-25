#ifndef BALONLAR_H
#define BALONLAR_H

#include <QPushButton>
#include <QMainWindow>
#include <QObject>
#include <QWidget>

class balon : public QPushButton
{
public:
    bool tiklandimi;
    explicit balon(QWidget *parent = 0);

public slots:
    void tikla();
};

#endif // BALON_H
