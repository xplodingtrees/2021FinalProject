#ifndef AUTHOR_H
#define AUTHOR_H

class Author {
private:
    string name;

public:
    Author();
    ~Author();

    //setters/getters
    string getName() const;
    void setName(string newName);
};

#include "Author.cpp"

#endif //AUTHOR_H
