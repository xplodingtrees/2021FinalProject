#include "Patron.h"

Patron::Patron() = default;

Patron::Patron(const string &name, const string &address, const string &phoneNum) : name(name), address(address),
                                                                                    phoneNum(phoneNum) {}

Patron::~Patron() = default;

std::string Patron::getName() const {
    return name;
}

std::string Patron::getAddress() const {
    return address;
}

std::string Patron::getPhoneNum() const {
    return phoneNum;
}

void Patron::setName(const string &newName) {
    name = newName;
}

void Patron::setAddress(const string &newAddress) {
    address = newAddress;
}

void Patron::setPhoneNum(const string &newPhoneNum) {
    phoneNum = newPhoneNum;
}


