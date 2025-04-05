#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QString>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class Nails {
public:
    QString id;
    QDateTime datetime_shipment;
    QDateTime datetime_sending;
    QString typeName;
    QString serialNum;
    QString material;
public:
    Nails() = default;

    Nails(const QString id, const QDateTime &shipment, const QDateTime &sending,
          const QString &typeName, const QString &serialNum, const QString &material)
        : id(id), datetime_shipment(shipment), datetime_sending(sending),
        typeName(typeName), serialNum(serialNum), material(material) {}

    QString getId() const { return id; }

    QDateTime getDatetimeShipment() const { return datetime_shipment; }
    void setDatetimeShipment(const QDateTime &value) { datetime_shipment = value; }

    QDateTime getDatetimeSending() const { return datetime_sending; }
    void setDatetimeSending(const QDateTime &value) { datetime_sending = value; }

    QString getTypename() const { return typeName; }
    void setTypename(const QString &value) { typeName = value; }

    QString getSerialNum() const { return serialNum; }
    void setSerialNum(const QString &value) { serialNum = value; }

    QString getMaterial() const { return material; }
    void setMaterial(const QString &value) { material = value; }
};


//синглтон класс
class ClientInterface {
public:

    //статическое свойство(поле класса, поле данных)
    //статик - значит что у всех одно и то же это поле,
    //обьекты всех классов будут обращаться к этой глобальной переменной (static)
    static ClientInterface * existing_object;

    //функция заменяет конструктор
    static ClientInterface * getInstance(QString root_url = "http://localhost:80/api") {
        //Проверить есть ли обьекты client interface, если нет, то
        if (existing_object == nullptr){
            //создаем новый обьект
            existing_object = new ClientInterface(root_url);
        }
        //возвращаем существующий если нет
        //qDebug() << "***getInstance(): existing_object = " << Qt::hex << existing_object;
        return existing_object;
    }

    static removeInstance() {
        if (existing_object) {
            delete existing_object;
        }
        existing_object = nullptr;
    }

    Nails GetNail(const unsigned int id);
    Nails UpdateNail(const unsigned int id, QJsonObject data);
    Nails CreateNail(QJsonObject data);
    void DeleteNail(const unsigned int id);
    QList<Nails> GetNails();

    ~ClientInterface() {
        delete m_client;
    }

    QString getRootUrl() {
        return m_root_url;
    }

protected:
    ClientInterface(const QString & root_url)
        :m_root_url(root_url)
    {
        m_client = new QNetworkAccessManager();
    }

    QNetworkAccessManager * m_client = nullptr;
    QString m_root_url;
};

class ClientInterfaceDecorator : public ClientInterface {
public:
    ClientInterfaceDecorator(ClientInterface* ci): ClientInterface(ci->getRootUrl()), m_wrapped(ci) {}

    QJsonDocument MakeRequest(const QString& url, const QString& id="", const QString& method="get", QByteArray requestData=QByteArray()) {
        QNetworkRequest request;
        request.setUrl(QUrl(m_root_url + url + id));
        request.setHeader(
            QNetworkRequest::ContentTypeHeader,
            "application/json");
        QNetworkReply * reply;

        if (method=="delete") {
            reply = m_client->deleteResource(request);
        } else if (method=="get")
            reply = m_client->get(request);
        else if (method=="post")
            reply = m_client->post(request, requestData);
        else if (method=="put")
            reply = m_client->put(request, requestData);
        else if (method=="patch") {
            request.setRawHeader("X-HTTP-Method-Override", "PATCH");
            reply = m_client->put(request, requestData);
        }

        QEventLoop evtLoop;
        QObject::connect(reply, &QNetworkReply::finished, &evtLoop, &QEventLoop::quit); //СИГНАЛЫ О ГОТОВНОСТИ
        QObject::connect(reply, &QNetworkReply::errorOccurred, &evtLoop, &QEventLoop::quit); //<<<СИГНАЛЫ: ВСЕ ОШИБКИ
        QObject::connect(reply, &QNetworkReply::sslErrors, &evtLoop, &QEventLoop::quit);  //<<<<<Тоже ошибко всякие
        evtLoop.exec();

        QJsonDocument jsonDoc = (QJsonDocument::fromJson(reply->readAll()));

        return jsonDoc;
    }

    QList<Nails> ParseNails(const QJsonArray& arr){
        QList<Nails> nailsList;

        for (const QJsonValue &value : arr) {
            QJsonObject nailObject = value.toObject();

            QString id = QString::number(nailObject["id"].toDouble());
            QDateTime shipment = QDateTime::fromString(nailObject["datetime_shipment"].toString(), Qt::ISODate);
            QDateTime sending = QDateTime::fromString(nailObject["datetime_sending"].toString(), Qt::ISODate);
            QString typeName = nailObject["typename"].toString();
            QString serialNum = nailObject["serialNum"].toString();
            QString material = nailObject["material"].toString();

            nailsList.append(Nails(id, shipment, sending, typeName, serialNum, material));
        }

        return nailsList;
    }

    Nails ParseNail(const QJsonObject& obj) {
        QString id = QString::number(obj["id"].toDouble());
        QDateTime shipment = QDateTime::fromString(obj["datetime_shipment"].toString(), Qt::ISODate);
        QDateTime sending = QDateTime::fromString(obj["datetime_sending"].toString(), Qt::ISODate);
        QString typeName = obj["typename"].toString();
        QString serialNum = obj["serialNum"].toString();
        QString material = obj["material"].toString();
        Nails result(id, shipment, sending, typeName, serialNum, material);
        return result;
    }

private:
    ClientInterface* m_wrapped;
};

#endif // CLIENTINTERFACE_H
