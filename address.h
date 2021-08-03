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
    Address(QString streetAddress, QString city, QString state, int postalCode);
    QJsonObject toJsonObject();

    void setStreetAddress(QString street);
    void setCity(QString city);
    void setState(QString state);
    void setPostalCode(int postalCode);

    QString getStreetAddress();
    QString getCity();
    QString getState();
    int getPostalCode();

private:
    QString city;
    int postalCode;
    QString state;
    QString streetAddress;
};

#endif // ADDRESS_H
