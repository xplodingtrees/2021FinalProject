#include "Patron.h"

Patron::Patron() {

}

Patron::~Patron() {

}

string Patron::getName() const {
    return name;
}

string Patron::getAddress() const {
    return address;
}

string Patron::getPhoneNum() const {
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
