#pragma once
#include <exception>
#include <string>
using namespace std;

class DomainException : public exception {
    string msg;
public:
    DomainException(string m) : msg(m) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};
