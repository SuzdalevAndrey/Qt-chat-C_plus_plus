#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>

namespace Ui {
class privateMessageWindow;
}

class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

private:
    Ui::privateMessageWindow *ui;
};

#endif // CHATWINDOW_H
