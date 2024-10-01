#include <QApplication>

#include "loginwindow.h"
#include "dbvalidator.h"
#include "usercontroller.h"

#include <QDebug>


int main(int argc, char *argv[]) try {
    std::string dbName = "app";
    if (argc > 1) {
        dbName = argv[1];
    }

    QApplication app(argc, argv);

    DBValidator dbValidator(dbName);
    dbValidator.validateDatabase();

    UserController userController(dbValidator.getDBInstance());
    LoginWindow window(std::move(userController));
    window.show();

    return app.exec();
} catch (const std::exception &e) {
    qDebug() << e.what();
    return 1;
} catch(...) {
    return 1;
}
