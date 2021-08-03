#include "address.h"

Address::Address(QJsonObject obj)
{
    city = obj.value("city").toString();
    postalCode = obj.value("postalCode").toInt();
    state = obj.value("state").toString();
    streetAddress = obj.value("streetAddress").toString();
}

Address::Address() {
    city = " ";
    postalCode = 0;
    state = " ";
    streetAddress = " ";
}

Address::Address(QString streetAddress, QString city, QString state, int postalCode)
{
    this->streetAddress = streetAddress;
    this->city = city;
    this->state = state;
    this->postalCode = postalCode;
}

QJsonObject Address::toJsonObject()
{
    QJsonObject obj;
    obj.insert("city", QJsonValue::fromVariant(city));
    obj.insert("postalCode", QJsonValue::fromVariant(postalCode));
    obj.insert("state", QJsonValue::fromVariant(state));
    obj.insert("streetAddress", QJsonValue::fromVariant(streetAddress));
    return obj;
}

void Address::setStreetAddress(QString street)
{
    this->streetAddress = street;
}

void Address::setCity(QString city)
{
    this->city = city;
}

void Address::setState(QString state)
{
    this->state = state;
}

void Address::setPostalCode(int postalCode)
{
    this->postalCode = postalCode;
}

QString Address::getStreetAddress()
{
    return streetAddress;
}

QString Address::getCity()
{
    return city;
}

QString Address::getState()
{
    return state;
}

int Address::getPostalCode()
{
    return postalCode;
}
