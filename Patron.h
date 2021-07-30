#ifndef PATRON_H
#define PATRON_H

using namespace std;

class Patron {
private:
    string name;
    string address;
    string phoneNum;

public:
    Patron();
    Patron(const string &name, const string &address, const string &phoneNum);

    ~Patron();

    //setters/getters
    string getName() const;
    string getAddress() const;
    string getPhoneNum() const;
    void setName(const string &newName);
    void setAddress(const string &newAddress);
    void setPhoneNum(const string &newPhoneNum);
};

#include "Patron.cpp"

#endif //PATRON_H
