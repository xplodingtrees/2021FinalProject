#include "Library.h"
#include "memory"

using namespace std;

Library::Library(){}

Library::Library(const string &name, const string &address, const string &hours)
        : name(name), address(address), hours(hours){

    //shared_ptr<Comparator<shared_ptr<Book>>> bookComparator = make_shared<bookComparator>();
    //bookIndex = make_unique<BinarySearchTree<shared_ptr<Book>>>(bookComparator);

    patrons = make_unique<LinkedList<shared_ptr<Patron>>>();
    books = make_unique<LinkedList<shared_ptr<Book>>>();
    booksUnavailable = make_unique<LinkedList<shared_ptr<Book>>>();
    booksAvailable = make_unique<LinkedList<shared_ptr<Book>>>();
    dropBox = make_unique<LinkedStack<shared_ptr<Book>>>();

}

Library::~Library() {}

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
