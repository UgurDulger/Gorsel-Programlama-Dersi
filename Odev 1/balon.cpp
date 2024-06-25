#include "balon.h"
#include "QDebug"


balon::balon(QWidget *parrent):QPushButton(parrent)
{
    tiklandimi=false;
    connect(this,&QPushButton::clicked,this,&balon::tikla);
}

void balon::tikla()
{

    tiklandimi = true;

}
