#ifndef TABLEVALIDATOR_H
#define TABLEVALIDATOR_H

#include <string>


class TableValidator {
public:
    TableValidator(std::string_view tableName) : tableName(tableName) {}
    TableValidator(const TableValidator &other) = delete;
    TableValidator(TableValidator &&other) = default;
    virtual ~TableValidator() = default;

    TableValidator &operator=(const TableValidator &other) = delete;
    TableValidator &operator=(TableValidator &&other) = delete;

    virtual void validateTable() = 0;
    virtual void removeTable() = 0;

protected:
    enum class ValidationStatus {
        INVALID,
        NEED_UPDATE,
        VALID,
    };

    virtual bool tableExists() const = 0;
    virtual void createTable() = 0;

    virtual ValidationStatus checkTable() const = 0;
    virtual void updateTable() = 0;
    virtual void backupTable() = 0;
    virtual void restoreTable() = 0;

    const std::string tableName;
};


#endif // TABLEVALIDATOR_H
