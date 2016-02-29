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

    char continuar = 'S';
    while(true)
    {
        std::cout << "Digite um CEP: ";
        std::string cepBusca;
        std::cin >> cepBusca;

        QString cep(cepBusca.data());
        cep.replace("-", "");

        QEventLoop waitLoop;
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(QUrl("http://viacep.com.br/ws/" + cep + "/json")));
        QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
        waitLoop.exec();

        QJsonDocument doc(QJsonDocument::fromJson(reply->readAll()));
        QJsonObject json(doc.object());
        std::cout << "\n\n\n";
        if(json.find("erro") != json.end())
        {
            std::cout << "erro: " << std::boolalpha << json["erro"].toBool();
        }
        else
        {
            std::cout << "cep: "           << json["cep"].toString().toStdString() << '\n';
            std::cout << "logradouro: "    << json["logradouro"].toString().toStdString() << '\n';
            std::cout << "localidade: "    << json["localidade"].toString().toStdString() << '\n';
            std::cout << "uf: "            << json["uf"].toString().toStdString() << '\n';
            std::cout << "complemento: "   << json["complemento"].toString().toStdString() << '\n';
            std::cout << "bairro: "        << json["bairro"].toString().toStdString() << '\n';
            std::cout << "ibge: "          << json["ibge"].toString().toStdString() << '\n';
            std::cout << "gia: "           << json["gia"].toString().toStdString() << '\n';
        }

        std::cout << "\n\nDeseja buscar um novo CEP ? Sim(S)/Não(N): ";
        std::cin >> continuar;
        continuar = toupper(continuar);
        std::cout << "\n\n\n";

        if(continuar == 'N')
            exit(0);
    }

    return a.exec();
}
