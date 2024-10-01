#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QMessageBox>

#include "registerwindow.h"
#include "mainwindow.h"


LoginWindow::LoginWindow(UserController userController, QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::LoginWindow)
, userController(std::move(userController)) {
    ui->setupUi(this);
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_loginLEdit_textChanged(const QString &login) {
    int id = userController.findUserId(login.toStdString());
    if (id != -1) {
        ui->nameLbl->setText(login);
    }
    else {
        ui->nameLbl->clear();
    }
}

void LoginWindow::on_loginBtn_clicked() {
    std::string login = ui->loginLEdit->text().toStdString();
    std::string passwd = ui->passwdLEdit->text().toStdString();
    int id = userController.findUserId(login);
    if (id == -1) {
        QMessageBox::warning(this, "Ошибка входа", "Аккаунт с данным логином не существует");
        return;
    }
    if (userController.checkPasswd(id, passwd)) {
        this->hide();
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
        close();
    } else {
        QMessageBox::warning(this, "Ошибка входа", "Введен неверный пароль");
    }
}

void LoginWindow::on_registerBtn_clicked() {
    this->hide();
    RegisterWindow *registerWindow = new RegisterWindow(std::move(userController));
    registerWindow->show();
    close();
}

