#include "createchatwindow.h"
#include "ui_createchatwindow.h"

CreateChatWindow::CreateChatWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateChatWindow)
{
    ui->setupUi(this);
}

CreateChatWindow::~CreateChatWindow()
{
    delete ui;
}
