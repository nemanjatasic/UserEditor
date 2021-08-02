#ifndef USER_H
#define USER_H
#include "address.h"
#include <QDate>
#include <QString>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QMap>

class User
{
public:
    User();
    User(QJsonObject obj);
    QJsonObject toJsonObject();
//private:
    QString firstName;
    QString lastName;
    QString gender;
    QDate dateOfBirth;
    Address address;
    QMap<QString, QString> phoneNumbers;
};

#endif // USER_H
