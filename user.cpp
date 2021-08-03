#include "user.h"

User::User(QJsonObject obj)
{
    firstName = obj.value("firstName").toString();
    lastName = obj.value("lastName").toString();
    gender = obj.value("gender").toString();
    dateOfBirth = obj.value("dateOfBirth").toVariant().toDate();
    address = Address(obj.value("address").toObject());

    QJsonArray numbersArray = obj.value("phoneNumbers").toArray();
    for (auto numbers : numbersArray) {
        QJsonObject numbersObj = numbers.toObject();
        if (numbersObj.value("type").toString() == "home")
            phoneNumbers.insert("home", numbersObj.value("number").toVariant().toString());
        if (numbersObj.value("type").toString() == "mobile")
            phoneNumbers.insert("mobile", numbersObj.value("number").toVariant().toString());
    }
}

User::User()
{
    firstName = "   /   ";
    lastName = "   /   ";
    gender = "   /   ";
    dateOfBirth = QDate();
    address = Address();
    phoneNumbers.insert("home", "0");
    phoneNumbers.insert("mobile", "0");
}

QJsonObject User::toJsonObject()
{
    QJsonObject obj;
    obj.insert("firstName", QJsonValue::fromVariant(firstName));
    obj.insert("lastName", QJsonValue::fromVariant(lastName));
    obj.insert("gender", QJsonValue::fromVariant(gender));
    obj.insert("dateOfBirth", QJsonValue::fromVariant(dateOfBirth));

    QJsonObject addrObj = address.toJsonObject();
    obj.insert("address", addrObj);

    QJsonObject numberHome;
    QJsonObject numberMobile;
    numberHome.insert("type", QJsonValue::fromVariant("home"));
    numberHome.insert("number", QJsonValue::fromVariant(phoneNumbers.value("home")));
    numberMobile.insert("type", QJsonValue::fromVariant("mobile"));
    numberMobile.insert("number", QJsonValue::fromVariant(phoneNumbers.value("mobile")));
    QJsonArray numbersArray;
    numbersArray.append(numberHome);
    numbersArray.append(numberMobile);
    obj.insert("phoneNumbers", numbersArray);

    return obj;
}

void User::setFirstName(QString fName)
{
    firstName = fName;
}

void User::setLastName(QString lName)
{
    lastName = lName;
}

void User::setGender(QString userGender)
{
    gender = userGender;
}

void User::setAddress(Address &addr)
{
    address = Address(addr);
}

void User::setAddress(QString streetAddr, QString city, QString state, int postalCode)
{
    address = Address(streetAddr, city, state, postalCode);
}

void User::setDateOfBirth(QDate date)
{
    dateOfBirth = date;
}

void User::setHomePhoneNumber(QString number)
{
    phoneNumbers.insert("home", number);
}

void User::setMobilePhoneNUmber(QString number)
{
    phoneNumbers.insert("mobile", number);
}

QString User::getFirstName()
{
    return firstName;
}

QString User::getLastName()
{
    return lastName;
}

QString User::getGender()
{
    return gender;
}

Address User::getAddress()
{
    return address;
}

QDate User::getDateOfBirth()
{
    return dateOfBirth;
}

QString User::getHomePhoneNumber()
{
    return phoneNumbers.value("home");
}

QString User::getMobilePhoneNumber()
{
    return phoneNumbers.value("mobile");
}
