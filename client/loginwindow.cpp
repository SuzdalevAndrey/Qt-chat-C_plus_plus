#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(&SocketManager::instance(), &SocketManager::userAuthenticated, this, &LoginWindow::handleReceivedAuthSuccessful);
    connect(&SocketManager::instance(), &SocketManager::userAuthenticationFailed, this, &LoginWindow::handleReceivedAuthFailed);
    connect(this, &LoginWindow::autorizationUser, &SocketManager::instance(), &SocketManager::autorizationUser);
}

LoginWindow::LoginWindow(QString email, QString password, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->emailLineEdit->setText(email);
    ui->passwordLineEdit->setText(password);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginPushButton_clicked()
{
    QString email = ui->emailLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::critical(this, "Error", "Пожалуйста заполните все поля!");
        return;
    }
    else{
        emit autorizationUser(email, password);
    }
}

// void LoginWindow::handleReceivedData(QDataStream &data)
// {
//     // qDebug()<<"read...";
//     bool isLogin;
//     qint8 type;
//     data>>type;
//     qDebug()<<static_cast<int>(type);
//     if(static_cast<ActionType>(type)== ActionType::LOGIN_USER){
//         data>>isLogin;
//         if(isLogin){
//             QMessageBox::information(this, "Информация", "Вы успешно авторизовались!");
//             QString name;
//             data>>name;
//             emit loggedInSuccessfully(name);
//             this->close();
//         }
//         else{
//             QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль!");
//         }
//     }
// }


void LoginWindow::on_registrationPushButton_clicked()
{
    RegistrationWindow *registrationform = new RegistrationWindow();
    registrationform->show();
    this->close();
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}

void LoginWindow::handleReceivedAuthSuccessful(const QString &name)
{
    QMessageBox::information(this, "Информация", "Вы успешно авторизовались!");
    emit loggedInSuccessfully(name);
    this->close();
}

void LoginWindow::handleReceivedAuthFailed()
{
    QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль!");
}

