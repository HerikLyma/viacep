/**
  @file
  @author Herik Lima
*/

#ifndef FRMVIACEPCOMINTERFACE_H
#define FRMVIACEPCOMINTERFACE_H


#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class FrmViaCepComInterface;
}

class FrmViaCepComInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrmViaCepComInterface(QWidget *parent = 0);
    ~FrmViaCepComInterface();

private slots:
    void on_pshBtnBuscar_clicked();

private:
    Ui::FrmViaCepComInterface *ui;
};

#endif // FRMVIACEPCOMINTERFACE_H
