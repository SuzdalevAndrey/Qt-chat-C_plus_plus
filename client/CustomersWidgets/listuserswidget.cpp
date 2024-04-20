#include "listuserswidget.h"

void ListUsersWidget::add(QString userName)
{
    QPushButton *button = new QPushButton(userName);
    button->setFixedHeight(30);
    QListWidgetItem *item = new QListWidgetItem;
    this->addItem(item);
    this->setItemWidget(item, button);
    connect(button, &QPushButton::clicked, [this, item]() {
        int index = this->row(item);
        emit buttonClicked(index);
    });
}

ListUsersWidget::~ListUsersWidget(){}
