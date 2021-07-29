#include "Library.h"

Library::Library(){}

Library::Library(const string &name,const string &address,const string &hours)
        : name(name), address(address), hours(hours){ //, patrons(LinkedList<shared_ptr<Patron>>()) {

}

Library::~Library() {}

LinkedList<Book> Library::availableBooks() {
    return LinkedList<Book>();
}

LinkedList<Book> Library::checkedBooks() {
    return LinkedList<Book>();
}

LinkedList<Patron> Library::registeredPatrons() {
    return LinkedList<Patron>();
}

vector<Book> Library::searchBooks(string searchTerm) {
    return vector<Book>();
}

bool Library::addBook(Book aBook) {
    return false;
}

bool Library::removeBook(string bookTitle) {
    return false;
}

bool Library::addPatron(string name, string address, string phoneNum) {
    return false;
}

bool Library::checkOutBook(string phoneNum, string bookTitle) {
    return false;
}

bool Library::setHold(string phoneNum, string bookTitle) {
    return false;
}

bool Library::returnBook(string bookTitle) {
    return false;
}

bool Library::checkInBook() {
    return false;
}

void Library::load(string fileName) {

}

void Library::save(string fileName) {

}

string Library::getName() const {
    return name;
}

string Library::getAddress() const {
    return address;
}

string Library::getHours() const {
    return hours;
}

void Library::setName(const string &newName) {
    name = newName;
}

void Library::setAddress(const string &newAddress) {
    address = newAddress;
}

void Library::setHours(const string &newHours) {
    hours = newHours;
}
