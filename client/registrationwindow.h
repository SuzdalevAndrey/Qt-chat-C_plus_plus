#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>
#include "loginwindow.h"
#include "socketmanager.h"
#include "qmessagebox.h"

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:
    void on_loginPushButton_clicked();

    void on_registerationPushButton_clicked();

signals:
    void registrationUser(authData& user);
private:
    void handleReceivedRegistrationSuccessful();
    void handleReceivedRegistrationFailed();

private:
    Ui::RegistrationWindow *ui;
};

#endif // REGISTRATIONWINDOW_H
