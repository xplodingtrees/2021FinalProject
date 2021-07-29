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
    ~Patron();

    //setters/getters
    string getName() const;
    string getAddress() const;
    string getPhoneNum() const;
    void setName(string newName);
    void setAddress(string newAddress);
    void setPhoneNum(string newPhoneNum);

};

#include "Patron.cpp"

#endif //PATRON_H
