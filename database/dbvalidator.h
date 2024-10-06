#ifndef DBVALIDATOR_H
#define DBVALIDATOR_H


#include <string>
#include <vector>

#include <pqxx/pqxx>

#include "tablevalidator.h"


class DBValidator final{
public:
    DBValidator(std::string_view dbName);
    ~DBValidator();

    pqxx::connection *getDBInstance();

    void validateDatabase();
    void removeDatabase();

private:
    bool dbExists() const;
    void createDatabase();

    void validateTables();

    const std::string dbName;
    pqxx::connection *db = nullptr;

    std::vector<TableValidator*> validators;
};


#endif // DBVALIDATOR_H
