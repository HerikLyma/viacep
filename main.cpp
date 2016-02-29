#include <iostream>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QEventLoop waitLoop;
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl("http://viacep.com.br/ws/01328010/json")));
    QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
    waitLoop.exec();

    QJsonDocument doc(QJsonDocument::fromJson(reply->readAll()));
    QJsonObject json(doc.object());

    if(json.find("erro") != json.end())
    {
        qDebug() << "erro: "           << json["erro"].toBool();
    }
    else
    {
        qDebug() << "cep: "           << json["cep"].toString();
        qDebug() << "logradouro: "    << json["logradouro"].toString();
        qDebug() << "localidade: "    << json["localidade"].toString();
        qDebug() << "uf: "            << json["uf"].toString();
        qDebug() << "complemento: "   << json["complemento"].toString();
        qDebug() << "bairro: "        << json["bairro"].toString();
        qDebug() << "ibge: "          << json["ibge"].toString();
        qDebug() << "gia: "           << json["gia"].toString();
    }

    return a.exec();
}
