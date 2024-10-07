#include "registerwindow.h"
#include "ui_registerwindow.h"

#include <QMessageBox>

#include "authexceptions.h"
#include "mainwindow.h"


RegisterWindow::RegisterWindow(UserController userController, QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::RegisterWindow)
, userController(std::move(userController)) {
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow() {
    delete ui;
}

void RegisterWindow::on_registerBtn_clicked() {
    std::string login = ui->loginLEdit->text().toStdString();
    std::string passwd = ui->passwdLEdit->text().toStdString();
    int id = userController.findUserId(login);
    if (id != -1) {
        QMessageBox::warning(this, "Ошибка регистрации", "Аккаунт с данным логином уже существует");
        return;
    }
    try {
        userController.createUser(login, passwd);
        QMessageBox::information(this, "", "Аккаунт успешно создан");
        this->hide();
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
        close();
    } catch (auth::AuthException &e) {
        QMessageBox::warning(this, "Ошибка регистрации", e.what());
    }
}
