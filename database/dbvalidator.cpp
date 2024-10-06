#include "dbvalidator.h"

#include "usertablevalidator.h"


DBValidator::DBValidator(std::string_view dbName) : dbName(dbName) {
    if (dbName.empty()) {
        throw std::runtime_error("DBValidator: Database name is empty");
    }

    // push validators to all tables
    validators.push_back(new UserTableValidator("Users", getDBInstance()));
}

DBValidator::~DBValidator() {
    for (auto i : validators) {
        delete i;
    }
}

pqxx::connection *DBValidator::getDBInstance() {
    if (!db || !db->is_open()) {
        delete db;
        try {
            db = new pqxx::connection("dbname=" + dbName + " user=postgres");
        } catch(pqxx::failure &e) {
            std::string text = "DBValidator: ";
            text.append(e.what());
            throw std::runtime_error(text);
        }
    }
    return db;
}

void DBValidator::removeDatabase() {
    try {
        pqxx::connection db("dbname=postgres user=postgres");
        pqxx::nontransaction nonTr(db);
        nonTr.exec("DROP DATABASE IF EXISTS " + dbName);
    } catch (pqxx::failure &e) {
        std::string text = "DBValidator: ";
        text.append(e.what());
        throw std::runtime_error(text);
    }
}

void DBValidator::validateDatabase() {
    if (!dbExists()) {
        createDatabase();
    }

    validateTables();
}

bool DBValidator::dbExists() const {
    try {
        pqxx::connection db("dbname=postgres user=postgres");
        pqxx::nontransaction nonTr(db);
        pqxx::result result = nonTr.exec("SELECT 1 FROM pg_database WHERE datname = "
                                         + nonTr.quote(dbName));
        return !result.empty();
    } catch (pqxx::failure &e) {
        std::string text = "DBValidator: ";
        text.append(e.what());
        throw std::runtime_error(text);
    }
}

void DBValidator::createDatabase() {
    try {
        pqxx::connection db("dbname=postgres user=postgres");
        pqxx::nontransaction nonTr(db);
        nonTr.exec("CREATE DATABASE " + dbName);
    } catch (pqxx::failure &e) {
        std::string text = "DBValidator: ";
        text.append(e.what());
        throw std::runtime_error(text);
    }
}

void DBValidator::validateTables() {
    for (auto i : validators) {
        i->validateTable();
    }
}
