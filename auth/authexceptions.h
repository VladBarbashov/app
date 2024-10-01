#ifndef AUTHEXCEPTIONS_H
#define AUTHEXCEPTIONS_H


#include <exception>


namespace auth {
    class InvalidLogin : public std::exception {
    public:
        const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
            return "Login is empty or contains invalid characters";
        }
    };

    class InvalidPasswd : public std::exception {
    public:
        const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
            return "Password is short or contains invalid characters";
        }
    };

    class WrongLogin : public std::exception {
    public:
        const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
            return "There is no account with that login";
        }
    };

    class WrongPasswd : public std::exception {
    public:
        const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
            return "Wrong password";
        }
    };
}


#endif // AUTHEXCEPTIONS_H
