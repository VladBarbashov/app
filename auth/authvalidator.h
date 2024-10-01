#ifndef AUTHVALIDATOR_H
#define AUTHVALIDATOR_H


#include <string>


class AuthValidator {
public:
    AuthValidator() = default;
    AuthValidator(const AuthValidator &other) = delete;
    AuthValidator(AuthValidator &&other) = default;
    virtual ~AuthValidator() = default;

    AuthValidator &operator=(const AuthValidator &other) = delete;
    AuthValidator &operator=(AuthValidator &&other) = delete;

    virtual void validate(std::string_view str) const = 0;
};


#endif // AUTHVALIDATOR_H
