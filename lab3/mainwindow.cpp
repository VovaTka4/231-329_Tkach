#include "mainwindow.h"
#include "./ui_mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //докажем что одно и то же создается
    m_interface = ClientInterface::getInstance();
    // ClientInterface * interface2 = ClientInterface::getInstance();
    // ClientInterface * interface3 = ClientInterface::getInstance();
    ui->tableWidget->setColumnCount(6);

    QStringList headers;
    headers << "ID" << "Дата поставки" << "Дата отправки" << "Тип" << "Серийный номер" << "Материал";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);

    ui->tableWidget->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    /*QNetworkAccessManager * nam = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:80/api/nails/"));
    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json");
    QNetworkReply * reply = nam->get(request);

    QEventLoop evtLoop;
    connect(reply, &QNetworkReply::finished, &evtLoop, &QEventLoop::quit); //СИГНАЛЫ О ГОТОВНОСТИ
    connect(reply, &QNetworkReply::errorOccurred, &evtLoop, &QEventLoop::quit); //<<<СИГНАЛЫ: ВСЕ ОШИБКИ
    connect(reply, &QNetworkReply::sslErrors, &evtLoop, &QEventLoop::quit);  //<<<<<Тоже ошибко всякие
    evtLoop.exec();*/ //Здесь 1) код текущей функции "встает на паузу",
                    //а 2) программа "занимается своими остальными фоновыми делами"(цикл обработки фоновых сообщений)
    //про exec в main.cpp
    //когда в этом коде exec получит сообщение любое из обрабатываемых, то прервется exec и вернет туда где конец exec
    //выход происходи по сигналу quit (третий аргумент)
    // qDebug()
    //     << "**RESPONSE: "
    //     << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
    //     << reply->errorString()
    //     << reply->readAll();

    // QByteArray responseData = reply->readAll();

    // QJsonDocument jsonData = QJsonDocument::fromJson(responseData);

    // QList<Nails> nailsList;
    // QJsonArray nailsArray = jsonData.array();

    // for (const QJsonValue &value : nailsArray) {
    //     QJsonObject nailObject = value.toObject();

    //     QDateTime shipment = QDateTime::fromString(nailObject["datetime_shipment"].toString(), Qt::ISODate);
    //     QDateTime sending = QDateTime::fromString(nailObject["datetime_sending"].toString(), Qt::ISODate);
    //     QString typeName = nailObject["typename"].toString();
    //     QString serialNum = nailObject["serialNum"].toString();
    //     QString material = nailObject["material"].toString();

    //     nailsList.append(Nails(shipment, sending, typeName, serialNum, material));
    // }

    // for (const Nails &nail : nailsList) {
    //     qDebug() << "Дата поставки: " << nail.getDatetimeShipment().toString(Qt::ISODate)
    //              << "Дата отправки: " << nail.getDatetimeSending().toString(Qt::ISODate)
    //              << "Материал: " << nail.getMaterial()
    //              << "Тип: " << nail.getTypename()
    //              << "Серийник: " << nail.getSerialNum() << "\n";
    // }
    QList<Nails> nailsList = m_interface->GetNails();

    ui->tableWidget->setRowCount(nailsList.size());
    for (int row = 0; row < nailsList.size(); ++row) {
        const Nails &nail = nailsList[row];

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(nail.getId()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(nail.getDatetimeShipment().toString(Qt::ISODate)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(nail.getDatetimeSending().toString(Qt::ISODate)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(nail.getTypename()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(nail.getSerialNum()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(nail.getMaterial()));

        // qDebug()<<"ДЛЯ ТАБЛИЦЫ:::::::::::::";
        // qDebug()<<nail.getDatetimeShipment().toString(Qt::ISODate);
        // qDebug()<<nail.getDatetimeSending().toString(Qt::ISODate);
        // qDebug()<<nail.getTypename();
        // qDebug()<<nail.getSerialNum();
        // qDebug()<<nail.getMaterial();
    }

    ui->tableWidget->update();
}

void MainWindow::on_pushButton_2_clicked()
{
    Nails result = m_interface->GetNail(2002);

    // qDebug() << "ID: " << result.getId();
    // qDebug() << "Datetime Shipment: " << result.getDatetimeShipment().toString(Qt::ISODate);
    // qDebug() << "Datetime Sending: " << result.getDatetimeSending().toString(Qt::ISODate);
    // qDebug() << "Type: " << result.getTypename();
    // qDebug() << "Serial Number: " << result.getSerialNum();
    // qDebug() << "Material: " << result.getMaterial();

    ui->tableWidget->clearContents();

    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(result.getId()));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(result.getDatetimeShipment().toString(Qt::ISODate)));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(result.getDatetimeSending().toString(Qt::ISODate)));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(result.getTypename()));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(result.getSerialNum()));
    ui->tableWidget->setItem(0, 5, new QTableWidgetItem(result.getMaterial()));

    ui->tableWidget->update();

}


void MainWindow::on_pushButton_3_clicked()
{
    m_interface->DeleteNail(1996);

    ui->tableWidget->clearContents();

    ui->tableWidget->update();
}


void MainWindow::on_pushButton_4_clicked()
{
    QJsonObject data;

    data["datetime_shipment"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    data["datetime_sending"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    data["typename"] = "typeQT";
    data["serialNum"] = "QT524";
    data["material"] = "QTmetal";

    Nails result = m_interface->CreateNail(data);

    // qDebug() << "Datetime Shipment: " << result.getDatetimeShipment().toString(Qt::ISODate);
    // qDebug() << "Datetime Sending: " << result.getDatetimeSending().toString(Qt::ISODate);
    // qDebug() << "Type: " << result.getTypename();
    // qDebug() << "Serial Number: " << result.getSerialNum();
    // qDebug() << "Material: " << result.getMaterial();

    ui->tableWidget->clearContents();

    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(result.getId()));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(result.getDatetimeShipment().toString(Qt::ISODate)));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(result.getDatetimeSending().toString(Qt::ISODate)));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(result.getTypename()));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(result.getSerialNum()));
    ui->tableWidget->setItem(0, 5, new QTableWidgetItem(result.getMaterial()));

    ui->tableWidget->update();
}


void MainWindow::on_pushButton_5_clicked()
{
    QJsonObject data;

    // data["datetime_shipment"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    // data["datetime_sending"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    // data["typename"] = "typeQT";
    data["serialNum"] = "QT4QT";
    data["material"] = "QTA";

    Nails result = m_interface->UpdateNail(2002, data);

    // qDebug() << "Datetime Shipment: " << result.getDatetimeShipment().toString(Qt::ISODate);
    // qDebug() << "Datetime Sending: " << result.getDatetimeSending().toString(Qt::ISODate);
    // qDebug() << "Type: " << result.getTypename();
    // qDebug() << "Serial Number: " << result.getSerialNum();
    // qDebug() << "Material: " << result.getMaterial();

    ui->tableWidget->clearContents();

    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(result.getId()));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(result.getDatetimeShipment().toString(Qt::ISODate)));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(result.getDatetimeSending().toString(Qt::ISODate)));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(result.getTypename()));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(result.getSerialNum()));
    ui->tableWidget->setItem(0, 5, new QTableWidgetItem(result.getMaterial()));

    ui->tableWidget->update();
}

