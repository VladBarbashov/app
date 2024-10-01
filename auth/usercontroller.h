#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H


#include <string>

#include <pqxx/pqxx>

#include "loginvalidator.h"
#include "passwdvalidator.h"


class UserController final {
public:
    UserController(pqxx::connection *const db);
    UserController(const UserController &other) = delete;
    UserController(UserController &&other) = default;

    UserController &operator=(const UserController &other) = delete;
    UserController &operator=(UserController &&other) = delete;

    int findUserId(std::string_view login) const;
    void createUser(std::string_view login, std::string_view passwd);
    bool checkPasswd(int userId, std::string_view passwd) const;

private:
    pqxx::connection *const db = nullptr;

    LoginValidator loginValidator;
    PasswdValidator passwdValidator;
};


#endif // USERCONTROLLER_H
