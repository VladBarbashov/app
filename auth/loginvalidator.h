#ifndef LOGINVALIDATOR_H
#define LOGINVALIDATOR_H


#include "authvalidator.h"


class LoginValidator : public AuthValidator
{
public:
    LoginValidator() = default;

    void validate(std::string_view login) const override;
};


#endif // LOGINVALIDATOR_H
