#ifndef CREATECHATWINDOW_H
#define CREATECHATWINDOW_H

#include <QDialog>

namespace Ui {
class CreateChatWindow;
}

class CreateChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateChatWindow(QWidget *parent = nullptr);
    ~CreateChatWindow();

private:
    Ui::CreateChatWindow *ui;
};

#endif // CREATECHATWINDOW_H
