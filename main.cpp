#include "ReplyTimeout.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QNetworkAccessManager networkAccessManger;
    QNetworkReply* reply1 =
            networkAccessManger.get(QNetworkRequest(QUrl("http://www.mocky.io/v2/5bda3fd72f00000f4006d440")));

    auto replyTimeout = new ReplyTimeout(reply1, 1/*in milliseconds*/);
    auto replyConnection = QObject::connect(reply1, &QNetworkReply::finished, [reply1](){
        qDebug() << reply1->readAll();
    });
    QObject::connect(replyTimeout, &ReplyTimeout::timeout, [replyConnection](){
        QObject::disconnect(replyConnection);//дізконектимось від reply1, бо сигнал &QNetworkReply::finished заемітиться коли відбудеться таймаут і матиме пусте тіло
        qDebug() << "timeout\n\n";
    });

//--------------------------------------------------------------------------------//

    QJsonObject json;
    json.insert("name", "Pinkie Pie");
    QJsonDocument payload;
    payload.setObject(json);
    QNetworkRequest request(QUrl("http://www.mocky.io/v2/5bda3f512f00007f3706d43f"));
    request.setRawHeader("content-type", "application/json");
    QNetworkReply* reply2 =
            networkAccessManger.post(request, payload.toJson());

    auto replyTimeout2 = new ReplyTimeout(reply1, 10000);
    auto replyConnection2 = QObject::connect(reply2, &QNetworkReply::finished, [reply2](){
        qDebug() << reply2->readAll();
    });
    QObject::connect(replyTimeout2, &ReplyTimeout::timeout, [replyConnection2](){
        QObject::disconnect(replyConnection2);
        qDebug() << "timeout";
    });

    return a.exec();
}
