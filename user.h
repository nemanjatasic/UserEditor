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
    void setFirstName(QString fName);
    void setLastName(QString lName);
    void setGender(QString userGender);
    void setAddress(Address &addr);
    void setAddress(QString streetAddr, QString city, QString state, int postalCode);
    void setDateOfBirth(QDate date);
    void setHomePhoneNumber(QString number);
    void setMobilePhoneNUmber(QString number);
    QString getFirstName();
    QString getLastName();
    QString getGender();
    Address getAddress();
    QDate getDateOfBirth();
    QString getHomePhoneNumber();
    QString getMobilePhoneNumber();

private:
    QString firstName;
    QString lastName;
    QString gender;
    QDate dateOfBirth;
    Address address;
    QMap<QString, QString> phoneNumbers;
};

#endif // USER_H
