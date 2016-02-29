/**
  @file
  @author Herik Lima
*/

#include "frmviacepcominterface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FrmViaCepComInterface w;
    w.show();

    return a.exec();
}
