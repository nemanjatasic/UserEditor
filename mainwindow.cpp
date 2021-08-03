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
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    QFile input(path);

    if(!input.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::about(this, "Not Opened", "Not Opened!");

    data_json = input.readAll();
    doc = doc.fromJson(data_json);
    arr = doc.array();

    input.close();
}

void MainWindow::writeJSON() {
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
        name.append(it.getFirstName()).append(" ").append(it.getLastName());
        ui -> usersListWidget -> addItem(name);
    }
}

void MainWindow::addUser(User nUser)
{
    QJsonObject nObj = nUser.toJsonObject();
    arr.append(nObj);
    loadUsers();
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
        name.append(it.getFirstName()).append(" ").append(it.getLastName());
        if (name == item->text()) {
            ui -> firstNameOutputLabel -> setText(it.getFirstName());
            ui -> lastNameOutputLabel -> setText(it.getLastName());
            ui -> genderOutoupLabel -> setText(it.getGender());
            ui -> dateOutputLabel -> setText(it.getDateOfBirth().toString());
            ui -> addressOutputLabel -> setText(it.getAddress().getStreetAddress());
            ui -> cityOutputLabel -> setText(it.getAddress().getCity());
            ui -> stateOutputLabel -> setText(it.getAddress().getState());
            ui -> postalCodeOutputLabel -> setText(QVariant(it.getAddress().getPostalCode()).toString());

            ui -> phoneOutputList->clear();
            QString homeNumber;
            homeNumber.append("home").append(" : ").append(it.getHomePhoneNumber());
            ui -> phoneOutputList -> addItem(homeNumber);
            QString mobileNumber;
            mobileNumber.append("mobile").append(" : ").append(it.getMobilePhoneNumber());
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
        loadUsers();
    }
}

void MainWindow::on_newFilePushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Create new file:", qApp->applicationDirPath(), "All File (*.*) ;; JSON File (*.json)");

    if (!fileName.endsWith(".json"))
        fileName.append(".json");

    if (fileName != ".json") {
        ui -> addPushButton -> setEnabled(true);
        ui -> removePushButton -> setEnabled(true);
        ui -> usersListWidget -> clear();
        arr = QJsonArray();
        path = fileName;
        ui -> fileOutputLabel->setText(fileName.right(fileName.size() - qApp->applicationDirPath().size() - 1));
    }
}

void MainWindow::on_openFilePushButton_clicked()
{
    QString filter = "All File (*.*) ;; JSON File (*.json)";
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file:", qApp->applicationDirPath(), filter);

    if (!fileName.isEmpty()) {
        path = fileName;
        readJSON();
        loadUsers();
        ui -> addPushButton -> setEnabled(true);
        ui -> removePushButton -> setEnabled(true);
        ui -> fileOutputLabel->setText(fileName.right(fileName.size() - qApp->applicationDirPath().size() - 1));
    }
}

void MainWindow::on_saveFilePushButton_clicked()
{
    writeJSON();
}
