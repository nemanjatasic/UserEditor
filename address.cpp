#include "address.h"

Address::Address(QJsonObject obj)
{
    city = obj.value("city").toString();
    postalCode = obj.value("postalCode").toInt();
    state = obj.value("state").toString();
    streetAddress = obj.value("streetAddress").toString();
}

Address::Address() {
    city = "Belgrade";
    postalCode = 11000;
    state = "Serbia";
    streetAddress = "Knez Mihailova";
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
