#include "usercontroller.h"


UserController::UserController(pqxx::connection *const db) : db(db) {}

int UserController::findUserId(std::string_view login) const {
    try {
        pqxx::nontransaction nonTr(*db);
        pqxx::result result = nonTr.exec("SELECT id FROM users WHERE login=" + nonTr.quote(login));
        if (result.empty()) {
            return -1;
        }
        return result.at(0).at(0).as<int>();
    } catch (pqxx::failure &e) {
        std::string text = "UserController: ";
        text.append(e.what());
        throw std::runtime_error(text);
    }
}

void UserController::createUser(std::string_view login, std::string_view passwd) {
    try {
        loginValidator.validate(login);
        passwdValidator.validate(passwd);

        pqxx::nontransaction nonTr(*db);
        nonTr.exec("INSERT INTO users(login,passwd) VALUES("
                   + nonTr.quote(login) + ',' + nonTr.quote(passwd) + ')');
    } catch (pqxx::failure &e) {
        std::string text = "UserController: ";
        text.append(e.what());
        throw std::runtime_error(text);
    }
}

bool UserController::checkPasswd(int userId, std::string_view passwd) const {
    if (userId < 0) {
        return false;
    }
    try {
        pqxx::nontransaction nonTr(*db);
        pqxx::result result = nonTr.exec("SELECT * FROM users WHERE passwd="
                                         + nonTr.quote(passwd) + " AND id=" + std::to_string(userId));
        return !result.empty();
    } catch (pqxx::failure &e) {
        std::string text = "UserController: ";
        text.append(e.what());
        throw std::runtime_error(text);
    }
}
