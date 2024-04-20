#include "registrationwindow.h"
#include "ui_registrationform.h"

RegistrationWindow::RegistrationWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);
    connect(this, &RegistrationWindow::registrationUser, &SocketManager::instance(), &SocketManager::registerUser);
    connect(&SocketManager::instance(), &SocketManager::userRegistration, this, &RegistrationWindow::handleReceivedRegistrationSuccessful);
    connect(&SocketManager::instance(), &SocketManager::userRegistrationFailed, this, &RegistrationWindow::handleReceivedRegistrationFailed);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_loginPushButton_clicked()
{
    LoginWindow *loginForm = new LoginWindow();
    loginForm->show();
    this->close();
}

void RegistrationWindow::on_registerationPushButton_clicked()
{
    QString name = ui->namelineEdit_2->text();
    QString email = ui->emailLineEdit_2->text();
    QString password = ui->passwordLineEdit_2->text();

    if (name.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::critical(this, "Error", "Пожалуйста заполните все поля!");
        return;
    }
    else{
        authData user(name, email, password);
        emit registrationUser(user);
    }
}

void RegistrationWindow::handleReceivedRegistrationSuccessful()
{
    QMessageBox::information(this, "Информация", "Вы успешно зарегистрировались!");
    this->close();
}

void RegistrationWindow::handleReceivedRegistrationFailed()
{
    QMessageBox::critical(this, "Ошибка", "Такой email уже есть в системе!");
}

