#ifndef LISTUSERSWIDGET_H
#define LISTUSERSWIDGET_H

#include <QListWidget>
#include <QPushButton>

class ListUsersWidget : public QListWidget
{
    Q_OBJECT

public:
    ListUsersWidget(QWidget *parent = nullptr):QListWidget(parent){}
    void add(QString userName);
    ~ListUsersWidget();
signals:
    void buttonClicked(int index);
};

#endif // LISTUSERSWIDGET_H
