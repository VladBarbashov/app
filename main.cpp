#include <QApplication>
#include <QMessageBox>

#include "loginwindow.h"
#include "dbvalidator.h"
#include "usercontroller.h"


int main(int argc, char *argv[]) {
    std::string dbName = "app";
    if (argc > 1) {
        dbName = argv[1];
    }
    QApplication app(argc, argv);

    try {
        DBValidator dbValidator(dbName);
        dbValidator.validateDatabase();

        UserController userController(dbValidator.getDBInstance());
        LoginWindow window(std::move(userController));
        window.show();

        return app.exec();
    } catch (pqxx::failure &e) {
        QMessageBox::warning(nullptr, "Ошибка", "Ошибка при работе с базой данных!");
        return 1;
    } catch (...) {
        QMessageBox::warning(nullptr, "Ошибка", "Неизвестная ошибка!");
        return 1;
    }
}
