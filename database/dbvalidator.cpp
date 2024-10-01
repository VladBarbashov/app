#include "dbvalidator.h"

#include "usertablevalidator.h"


DBValidator::DBValidator(std::string_view dbName) : dbName(dbName) {
    if (dbName.empty()) {
        throw std::runtime_error("Database name is empty: DBValidator");
    }

    if (!dbExists()) {
        createDatabase();
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
        db = new pqxx::connection("dbname=" + dbName + " user=postgres");
    }
    return db;
}

void DBValidator::removeDatabase() {
    pqxx::connection db("dbname=postgres user=postgres");
    pqxx::nontransaction nonTr(db);
    nonTr.exec("DROP DATABASE IF EXISTS " + dbName);
}

void DBValidator::validateDatabase() {
    validateTables();
}

bool DBValidator::dbExists() const {
    pqxx::connection db("dbname=postgres user=postgres");
    pqxx::nontransaction nonTr(db);
    pqxx::result result = nonTr.exec("SELECT 1 FROM pg_database WHERE datname = " + nonTr.quote(dbName));
    return !result.empty();
}

void DBValidator::createDatabase() {
    pqxx::connection db("dbname=postgres user=postgres");
    pqxx::nontransaction nonTr(db);
    nonTr.exec("CREATE DATABASE " + dbName);
}

void DBValidator::validateTables() {
    for (auto i : validators) {
        i->validateTable();
    }
}
