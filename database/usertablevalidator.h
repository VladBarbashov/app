#ifndef USERTABLEVALIDATOR_H
#define USERTABLEVALIDATOR_H


#include <string>

#include <pqxx/pqxx>

#include "tablevalidator.h"


class UserTableValidator final : public TableValidator {
public:
    UserTableValidator(std::string_view tableName, pqxx::connection *db);

    void validateTable() override;
    void removeTable() override;

private:
    bool tableExists() const override;
    void createTable() override;

    ValidationStatus checkTable() const override;
    void updateTable() override;
    void backupTable() override;
    void restoreTable() override;

    pqxx::connection *db = nullptr;
};


#endif // USERTABLEVALIDATOR_H
