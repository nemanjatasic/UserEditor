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

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);
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


    prntUser.firstName = fName;
    prntUser.lastName = lName;
    prntUser.gender = gen;
    prntUser.dateOfBirth = date;
    prntUser.address.streetAddress = streetAddress;
    prntUser.address.city = city;
    prntUser.address.state = state;
    prntUser.address.postalCode = postalCode;
    prntUser.phoneNumbers.insert("home", homePhone);
    prntUser.phoneNumbers.insert("mobile", mobilePhone);

    emit accept(QDialog::Accepted);
}



