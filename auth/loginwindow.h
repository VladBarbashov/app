#ifndef APP_H
#define APP_H


#include <QMainWindow>

#include "usercontroller.h"


namespace Ui {
    class LoginWindow;
}

class LoginWindow : public QMainWindow {
    Q_OBJECT

public:
    LoginWindow(UserController userController, QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginLEdit_textChanged(const QString &arg1);

    void on_loginBtn_clicked();

    void on_registerBtn_clicked();

private:
    Ui::LoginWindow *ui;

    UserController userController;
};
#endif // APP_H
