#include "clientinterface.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QTableWidgetItem>

//инициализируем чтоб все работало, глобальная переменная
ClientInterface * ClientInterface::existing_object = nullptr;

Nails ClientInterface::GetNail(const unsigned int id)
{
    ClientInterfaceDecorator decorator(this);
    QJsonDocument jsonDoc = decorator.MakeRequest("/nails/", QString::number(id));

    // qDebug() << jsonDoc;

    QJsonObject rootObj = jsonDoc.object();

    // qDebug() << rootObj;

    Nails result = decorator.ParseNail(rootObj);

    return result;
}

Nails ClientInterface::UpdateNail(const unsigned int id, QJsonObject data)
{
    ClientInterfaceDecorator decorator(this);
    QJsonDocument jsonData(data);
    QByteArray requestData = jsonData.toJson();

    QJsonDocument jsonDoc = decorator.MakeRequest("/nails/", QString::number(id), "patch", requestData);

    QJsonObject rootObj = jsonDoc.object();

    Nails result = decorator.ParseNail(rootObj);

    return result;
}

Nails ClientInterface::CreateNail(QJsonObject data)
{
    ClientInterfaceDecorator decorator(this);
    QJsonDocument jsonData(data);
    QByteArray requestData = jsonData.toJson();

    QJsonDocument jsonDoc = decorator.MakeRequest("/nails/", "", "post", requestData);

    QJsonObject rootObj = jsonDoc.object();

    Nails result = decorator.ParseNail(rootObj);

    return result;
}

void ClientInterface::DeleteNail(const unsigned int id)
{
    ClientInterfaceDecorator decorator(this);
    decorator.MakeRequest("/nails/", QString::number(id), "delete");
}

QList<Nails> ClientInterface::GetNails()
{
    ClientInterfaceDecorator decorator(this);
    QJsonDocument jsonDoc = decorator.MakeRequest("/nails/");

    QJsonArray rootObj = jsonDoc.array();

    QList<Nails> result = decorator.ParseNails(rootObj);

    return result;
}
