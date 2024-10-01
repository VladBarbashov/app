#include "usertablevalidator.h"


UserTableValidator::UserTableValidator(std::string_view tableName, pqxx::connection *db)
: TableValidator(tableName), db(db) {}

void UserTableValidator::validateTable() {
    if (!tableExists()) {
        createTable();
    }

    switch(checkTable()) {
    case ValidationStatus::INVALID:
        throw std::runtime_error("Cant validate database");

    case ValidationStatus::NEED_UPDATE:
        updateTable();
        break;

    default:
        break;
    }
}

void UserTableValidator::removeTable() {
    pqxx::nontransaction nonTr(*db);
    nonTr.exec("DROP TABLE IF EXISTS " + tableName);
}

bool UserTableValidator::tableExists() const {
    pqxx::nontransaction nonTr(*db);
    pqxx::result result = nonTr.exec("SELECT 1 "
                                     "FROM information_schema.tables "
                                     "WHERE table_schema = 'public' "
                                     "AND table_name = " + nonTr.quote(tableName));
    return !result.empty();
}

void UserTableValidator::createTable() {
    pqxx::nontransaction nonTr(*db);
    nonTr.exec("CREATE TABLE IF NOT EXISTS " + tableName +
               "(id SERIAL PRIMARY KEY,"
               "login VARCHAR(30),"
               "passwd VARCHAR(50))");
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
