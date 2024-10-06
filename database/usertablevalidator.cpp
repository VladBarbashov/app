#include "usertablevalidator.h"


UserTableValidator::UserTableValidator(std::string_view tableName, pqxx::connection *db)
: TableValidator(tableName), db(db) {}

void UserTableValidator::validateTable() {
    if (!tableExists()) {
        createTable();
        return;
    }

    switch(checkTable()) {
    case ValidationStatus::INVALID:
        throw std::runtime_error("UserTableValidator: Cant validate users table");

    case ValidationStatus::NEED_UPDATE:
        updateTable();
        break;

    default:
        break;
    }
}

void UserTableValidator::removeTable() {
    try {
        pqxx::nontransaction nonTr(*db);
        nonTr.exec("DROP TABLE IF EXISTS " + tableName);
    } catch (pqxx::failure &e) {
        std::string text = "UserTableValidator: ";
        text.append(e.what());
        throw std::runtime_error(text);
    }
}

bool UserTableValidator::tableExists() const {
    try {
        pqxx::nontransaction nonTr(*db);
        pqxx::result result = nonTr.exec("SELECT 1 "
                                         "FROM information_schema.tables "
                                         "WHERE table_schema = 'public' "
                                         "AND table_name = " + nonTr.quote(tableName));
        return !result.empty();
    } catch (pqxx::failure &e) {
        std::string text = "UserTableValidator: ";
        text.append(e.what());
        throw std::runtime_error(text);
    }
}

void UserTableValidator::createTable() {
    try {
        pqxx::nontransaction nonTr(*db);
        nonTr.exec("CREATE TABLE IF NOT EXISTS " + tableName +
                   "(id SERIAL PRIMARY KEY,"
                   "login VARCHAR(30),"
                   "passwd VARCHAR(50))");
    } catch (pqxx::failure &e) {
        std::string text = "UserTableValidator: ";
        text.append(e.what());
        throw std::runtime_error(text);
    }
}

UserTableValidator::ValidationStatus UserTableValidator::checkTable() const{
    // need some checks
    return ValidationStatus::VALID;
}

void UserTableValidator::updateTable() {
    backupTable();
    removeTable();
    restoreTable();
}

void UserTableValidator::backupTable() {
    // backup
}

void UserTableValidator::restoreTable() {
    // restore backup data with new structure
}
