#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QMessageBox>
#include <QRegExp>
#include "user.h"
#include "mainwindow.h"
#include <QRegExp>
#include <QRegExpValidator>

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);

    QRegExp firstNameRegExp("([A-Z][a-zA-Z]+)( [A-Z][a-zA-Z]+)?");
    QRegExpValidator *firstNameValidator = new QRegExpValidator(firstNameRegExp, this);
    ui -> firstNameLineEdit -> setValidator(firstNameValidator);

    QRegExp lastNameRegExp("([A-Z][a-zA-Z]+)( [A-Z][a-zA-Z]+){0,2}");
    QRegExpValidator *lastNameValidator = new QRegExpValidator(lastNameRegExp, this);
    ui -> lastNameLineEdit -> setValidator(lastNameValidator);

    QIntValidator *postCodeValidator = new QIntValidator(0, 99999);
    ui -> postCodeLineEdit -> setValidator(postCodeValidator);

    QRegExp streetRegExp("[ a-zA-Z0-9-.]+");
    QRegExpValidator *streetValidator = new QRegExpValidator(streetRegExp, this);
    ui -> addressLineEdit -> setValidator(streetValidator);

    QRegExp cityRegExp("([A-Z][a-zA-Z]+)( [A-Z][a-zA-Z]+){0,3}");
    QRegExpValidator *cityNameValidator = new QRegExpValidator(cityRegExp, this);
    ui -> cityLineEdit -> setValidator(cityNameValidator);

    QRegExp stateRegExp("([A-Z][a-zA-Z]+)( [A-Z][a-zA-Z]+){0,2}");
    QRegExpValidator *stateNameValidator = new QRegExpValidator(stateRegExp, this);
    ui -> stateLineEdit -> setValidator(stateNameValidator);

    QRegExp phoneNumberRegExp("[0-9]{5,15}");
    QRegExpValidator *phoneNumberValidator = new QRegExpValidator(phoneNumberRegExp, this);
    ui -> homePhoneLineEdit -> setValidator(phoneNumberValidator);
    ui -> mobilePhoneLineEdit -> setValidator(phoneNumberValidator);
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::on_buttonBox_accepted()
{
    MainWindow *prnt = qobject_cast<MainWindow *>(this->parent());
    User &prntUser = prnt -> publicUser;

    QString fName = ui -> firstNameLineEdit->text();
    QString lName = ui -> lastNameLineEdit->text();
    QString gen = ui -> genderComboBox->itemText(ui -> genderComboBox -> currentIndex());
    QDate date = ui -> dateEdit -> date();
    QString streetAddress = ui -> addressLineEdit -> text();
    QString city = ui -> cityLineEdit -> text();
    QString state = ui -> stateLineEdit -> text();
    int postalCode = ui -> postCodeLineEdit -> text().toInt();
    QString homePhone = ui -> homePhoneLineEdit -> text();
    QString mobilePhone = ui -> mobilePhoneLineEdit -> text();

    prntUser.setFirstName(fName);
    prntUser.setLastName(lName);
    prntUser.setGender(gen);
    prntUser.setDateOfBirth(date);
    prntUser.setAddress(streetAddress, city, state, postalCode);
    prntUser.setHomePhoneNumber(homePhone);
    prntUser.setMobilePhoneNUmber(mobilePhone);

    emit accept(QDialog::Accepted); // signal to initiate adding new user object in QJsonArray
}
