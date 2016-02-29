#include "frmviacepcominterface.h"
#include "ui_frmviacepcominterface.h"

FrmViaCepComInterface::FrmViaCepComInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrmViaCepComInterface)
{
    ui->setupUi(this);
}

FrmViaCepComInterface::~FrmViaCepComInterface()
{
    delete ui;
}

void FrmViaCepComInterface::on_pshBtnBuscar_clicked()
{
    QString cep(ui->lnEdtCEPBusca->text());
    cep.replace("-", "");

    QEventLoop waitLoop;
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl("http://viacep.com.br/ws/" + cep + "/json")));
    QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
    waitLoop.exec();

    QJsonDocument doc(QJsonDocument::fromJson(reply->readAll()));
    QJsonObject json(doc.object());

    if(json.find("erro") != json.end())
    {
        json["erro"].toBool() ? ui->lnEdtErro->setText("true") : ui->lnEdtErro->setText("false");
    }
    else
    {
        ui->lnEdtCEP->setText(json["cep"].toString());
        ui->lnEdtLogradouro->setText(json["logradouro"].toString());
        ui->lnEdtLocalidade->setText(json["localidade"].toString());
        ui->lnEdtUF->setText(json["uf"].toString());
        ui->lnEdtComplemento->setText(json["complemento"].toString());
        ui->lnEdtBairro->setText(json["bairro"].toString());
        ui->lnEdtIBGE->setText(json["ibge"].toString());
        ui->lnEdtGIA->setText(json["gia"].toString());
        ui->lnEdtErro->setText("false");
    }
}
