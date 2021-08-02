#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "adduserdialog.h"
#include "user.h"
#include <QVector>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadUsers();
    void readJSON();
    void writeJSON();
    void addUser(User);
    QList<User> users;
    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray arr;
    QByteArray data_json;
    QJsonObject jObj;
    User publicUser;

signals:
    void accept(int);

private slots:
    void on_addPushButton_clicked();

    void on_usersListWidget_itemActivated(QListWidgetItem *item);

    void on_removePushButton_clicked();

    void onAddedUser(int);


private:
    Ui::MainWindow *ui;
    QDialog *addUserDialog;

};
#endif // MAINWINDOW_H
