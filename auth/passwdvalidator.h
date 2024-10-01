#ifndef PASSWDVALIDATOR_H
#define PASSWDVALIDATOR_H


#include "authvalidator.h"


class PasswdValidator : public AuthValidator
{
public:
    PasswdValidator() = default;

    void validate(std::string_view passwd) const override;
};


#endif // PASSWDVALIDATOR_H
