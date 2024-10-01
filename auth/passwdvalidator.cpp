#include "passwdvalidator.h"

#include "authexceptions.h"


void PasswdValidator::validate(std::string_view passwd) const {
    if (passwd.empty()) {
        throw auth::InvalidPasswd();
    }
}
