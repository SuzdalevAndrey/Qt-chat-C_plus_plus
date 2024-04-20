#include "mainwindow.h"
#include "CustomersWidgets/listuserswidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->loginPushButton->setText("Войти");
    connect(&SocketManager::instance(), &SocketManager::messageReceived, this, &MainWindow::handleReceivedMessage);
    connect(&SocketManager::instance(), &SocketManager::userListReceived, this, &MainWindow::handleReceivedListUsers);
    connect(&SocketManager::instance(), &SocketManager::newConnection, this, &MainWindow::handleReceivedNewUser);
    connect(&SocketManager::instance(), &SocketManager::disconnection, this, &MainWindow::handleReceivedDisconnection);
    connect(this, &MainWindow::sendMessage, &SocketManager::instance(), &SocketManager::sendMessage);
    connect(this, &MainWindow::sendPrivateMessage, &SocketManager::instance(), &SocketManager::sendPrivateMessage);
    connect(this, &MainWindow::logout, &SocketManager::instance(), &SocketManager::logout);
    connect(ui->usersListWidget, &ListUsersWidget::buttonClicked, this, &MainWindow::handleReceivedIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    SocketManager::instance().connectSocket();
}

void MainWindow::on_pushButton_2_clicked()
{
    sendMessageToServer();
}


void MainWindow::on_lineEdit_returnPressed()
{
    sendMessageToServer();
}

void MainWindow::on_loginPushButton_clicked()
{
    if(!isLogin){
        LoginWindow *loginForm = new LoginWindow();
        connect(loginForm, &LoginWindow::loggedInSuccessfully, this, &MainWindow::handleLoginSuccess);
        connect(loginForm, &LoginWindow::closed, loginForm, &QObject::deleteLater);
        loginForm->show();
    }
    else{
        ui->nameUserLabel->setText("");
        ui->loginPushButton->setText("Войти");
        isLogin = false;
        ui->usersListWidget->clear();
        ui->ChatTextBrowser->clear();
        emit logout();
    }
}

void MainWindow::handleLoginSuccess(const QString &name)
{
    ui->nameUserLabel->setText(name);
    ui->loginPushButton->setText("Выйти");
    isLogin = true;
}

void MainWindow::handleReceivedMessage(const message &message)
{
    ui->ChatTextBrowser->append(message.getSender().getName() + ": " + message.getMessage());
    // qDebug()<<message.getSender() + ": " + message.getMessage();
}

void MainWindow::handleReceivedListUsers(const userList &users)
{
    ui->usersListWidget->clear();
    for(auto user : users.getUsers()){
        ui->usersListWidget->add(user.getName());
    }
}

void MainWindow::handleReceivedNewUser(const userInfo &user)
{
    ui->usersListWidget->add(user.getName());
}

void MainWindow::handleReceivedDisconnection(const userList &users)
{
    ui->usersListWidget->clear();
    for(auto user : users.getUsers()){
        ui->usersListWidget->add(user.getName());
    }
}

void MainWindow::sendMessageToServer()
{
    if(isLogin){
        if(indexRecipient == -1){
            message msg;
            msg.setMessage(ui->lineEdit->text());
            emit sendMessage(msg);
        }
        else{
            privateMessage msg;
            msg.setMessage(ui->lineEdit->text());
            // userInfo user;
            // user.setUserName(users[index].getName());
            // user.setUserEmail(users[index].getEmail());
            // msg.setRecipient(user);
            emit sendPrivateMessage(msg, indexRecipient);
        }
        ui->lineEdit->setText("");
    }
    else{
        QMessageBox::critical(this, "Error", "Пожалуйста авторизуйтесь для отправки сообщений!");
    }
}

void MainWindow::handleReceivedIndex(const int &index)
{
    this->indexRecipient = index;
}

