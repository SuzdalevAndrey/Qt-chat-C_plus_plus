#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>
#include "socketmanager.h"
#include "loginwindow.h"
// #include "D:\data\userlist.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_returnPressed();

    void on_loginPushButton_clicked();

signals:
    void sendMessage(message& message);

    void sendPrivateMessage(privateMessage& message, int indexRecipient);

    void logout();

private:
    void handleLoginSuccess(const QString& name);

    void handleReceivedMessage(const message& message);

    void handleReceivedListUsers(const userList& users);

    void handleReceivedNewUser(const userInfo& user);

    void handleReceivedDisconnection(const userList &users);

    void sendMessageToServer();

    void handleReceivedIndex(const int &index);

    Ui::MainWindow *ui;
    bool isLogin = false;
    int indexRecipient = -1;
};
#endif // MAINWINDOW_H
