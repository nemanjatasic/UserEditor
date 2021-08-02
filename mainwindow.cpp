#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "adduserdialog.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include "user.h"
#include <QString>
#include <QIODevice>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QListWidget>
#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readJSON();
    loadUsers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddedUser(int signalValue) {
    if (signalValue == QDialog::Accepted)
    addUser(publicUser);
}

void MainWindow::readJSON()
{
    QString path = qApp->applicationDirPath();
    path.append("/users.json");
    QFile input(path);

    if(!input.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::about(this, "Not Opened", "Not Opened!");

    data_json = input.readAll();
    doc = doc.fromJson(data_json);
    arr = doc.array();

    input.close();
}

void MainWindow::writeJSON() {
    QString path = qApp->applicationDirPath();
    path.append("/users.json");
    QFile output(path);

    if(!output.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::about(this, "Not Opened", "Not Opened!");

    doc = QJsonDocument(arr);
    data_json = doc.toJson();
    output.write(data_json);
    output.close();
}

void MainWindow::loadUsers()
{
    users.clear();
    ui -> usersListWidget -> clear();
    for (auto jsonObj : arr) {
        jObj = jsonObj.toObject();
        User newUser(jObj);
        users.append(newUser);
    }

    for (auto it : users) {
        QString name;
        name.append(it.firstName).append(" ").append(it.lastName);
        ui -> usersListWidget -> addItem(name);
    }
}

void MainWindow::addUser(User nUser)
{
    QJsonObject nObj = nUser.toJsonObject();
    arr.append(nObj);
    loadUsers();
    writeJSON();
}

void MainWindow::on_addPushButton_clicked()
{
    addUserDialog = new AddUserDialog(this);
    QObject::connect(addUserDialog, SIGNAL(accept(int)), this, SLOT(onAddedUser(int)));
    addUserDialog->exec();
}

void MainWindow::on_usersListWidget_itemActivated(QListWidgetItem *item)
{
    for (auto it : users) {
        QString name;
        name.append(it.firstName).append(" ").append(it.lastName);
        if (name == item->text()) {
            ui -> firstNameOutputLabel -> setText(it.firstName);
            ui -> lastNameOutputLabel -> setText(it.lastName);
            ui -> genderOutoupLabel -> setText(it.gender);
            ui -> dateOutputLabel -> setText(it.dateOfBirth.toString());
            ui -> addressOutputLabel -> setText(it.address.streetAddress);
            ui -> cityOutputLabel -> setText(it.address.city);
            ui -> stateOutputLabel -> setText(it.address.state);
            ui -> postalCodeOutputLabel -> setText(QVariant(it.address.postalCode).toString());

            ui -> phoneOutputList->clear();
            QString homeNumber;
            homeNumber.append("home").append(" : ").append(it.phoneNumbers.value("home"));
            ui -> phoneOutputList -> addItem(homeNumber);
            QString mobileNumber;
            mobileNumber.append("mobile").append(" : ").append(it.phoneNumbers.value("mobile"));
            ui -> phoneOutputList -> addItem(mobileNumber);
        }
    }
}

void MainWindow::on_removePushButton_clicked()
{
    QString message = "Are you sure you want to delete a '";
    message.append(ui->usersListWidget->currentItem()->text());
    message.append("'?");
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete user", message, QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        arr.removeAt(ui->usersListWidget->currentRow());
        writeJSON();
        loadUsers();
    }
}
