#ifndef ADDRESS_H
#define ADDRESS_H
#include <QString>
#include <QString>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>

class Address
{
public:
    Address(QJsonObject obj);
    Address();
    QJsonObject toJsonObject();
//private:
    QString city;
    int postalCode;
    QString state;
    QString streetAddress;
};

#endif // ADDRESS_H
