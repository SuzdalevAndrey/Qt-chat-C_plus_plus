#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "registrationwindow.h"
#include "mainwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    LoginWindow(QString email, QString password, QWidget *parent=nullptr);
    ~LoginWindow();

private slots:
    void on_loginPushButton_clicked();

    void on_registrationPushButton_clicked();

signals:
    void loggedInSuccessfully(const QString& name);
    void autorizationUser(const QString& email, const QString& password);
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    void handleReceivedAuthSuccessful(const QString& name);
    void handleReceivedAuthFailed();

    Ui::LoginWindow *ui;
};

#endif // LOGIN_H
