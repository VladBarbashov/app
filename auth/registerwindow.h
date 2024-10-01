#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H


#include <QMainWindow>

#include "usercontroller.h"


namespace Ui {
    class RegisterWindow;
}

class RegisterWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit RegisterWindow(UserController userController, QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_registerBtn_clicked();

private:
    Ui::RegisterWindow *ui;

    UserController userController;
};


#endif // REGISTERWINDOW_H
