#include "Author.h"

Author::Author() {
}

Author::Author(string authName) : name(authName) {
}


void Author::setName(const string newName) {
name = newName;
}

string Author::getName() const {
    return name;
}

