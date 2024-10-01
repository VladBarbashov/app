#include "loginvalidator.h"

#include "authexceptions.h"


void LoginValidator::validate(std::string_view login) const {
    if (login.empty()) {
        throw auth::InvalidLogin();
    }
}
