#include "Book.h"
Book::Book() : isAvailable(true), isbn(0), pages(0) {

}

Book::Book(const string &aTitle,const int &aisbn,const string &aPubDate,const string &aPublisher,const int &aPages) : isAvailable(true), title(aTitle), isbn(aisbn), pubDate(aPubDate), publisher(aPublisher), pages(aPages) {

}

Book::~Book() = default;

bool Book::addHold(shared_ptr<Patron> &aPatron) {
    if(isAvailable) {
        currentPatron = aPatron;
        setIsAvailable(false);
    } else {
        patronsOnHold.enqueue(aPatron);
    }
    return true;
}

bool Book::nextHold() {
    bool returnVal;
    if(isOnHold()) {
        setPatron(patronsOnHold.peekFront());// Puts the first one on hold into the current patron set
        returnVal = patronsOnHold.dequeue();
    } else {
        returnVal = false;
    }
    return returnVal;
}

bool Book::isOnHold() {
    return (!patronsOnHold.isEmpty());
}

bool Book::addAuthor(const shared_ptr<Author> &anAuthorPtr) {
    return authors.insert(authors.getLength() + 1,anAuthorPtr);
}

bool Book::removeAuthor(const shared_ptr<Author> &anAuthor) {
    bool found = false;
    int i = 0;
    while(!found && i < authors.getLength()) {
        if(authors.getEntry(i) == anAuthor) {
            found = authors.remove(i);
        }
        i++;
    }
    return found;
}


vector<shared_ptr<Author>> Book::getAuthors() const {
    vector<shared_ptr<Author>> authorVector;
    for(int index = 1; index <= authors.getLength(); index++){
        authorVector.push_back(authors.getEntry(index));
    }//end for

    return authorVector;
}

/**##############################################################################################################
 * getters and setters
 * */

string Book::getTitle() const {
    return title;
}

int Book::getIsbn() const {
    return isbn;
}

string Book::getPubDate() const {
    return pubDate;
}

string Book::getPublisher() const {
    return publisher;
}

int Book::getPages() const {
    return pages;
}

bool Book::getIsAvailable() const {
    return isAvailable;
}

void Book::setTitle(const string &newTitle) {
    title = newTitle;
}

void Book::setIsbn(const int &newIsbn) {
    isbn = newIsbn;
}

void Book::setPubDate(const string &newPubDate) {
    pubDate = newPubDate;
}

void Book::setPublisher(const string &newPublisher) {
    publisher = newPublisher;
}

void Book::setPages(const int &newPages) {
    pages = newPages;
}

void Book::setIsAvailable(const bool &status) {
    isAvailable = status;
}

shared_ptr<Patron> Book::getPatron() const {
    return currentPatron;
}

void Book::setPatron(const shared_ptr<Patron> &aPatron) {
    currentPatron = aPatron;
}

/**##############################################################################################################
 * friend functions
 * */

ostream& operator<<(ostream& out, const Book &book) {
    out << "Title: " << book.getTitle() << endl;

    vector<shared_ptr<Author>> authList = book.getAuthors();
    if(authList.size() > 0) {
        cout << "Author: " << authList[0]->getName() << endl;
    } else {
        cout << "No Author Found" << endl;
    }

    out << "Checked out by: ";

    if(book.getIsAvailable())
    {
        out << "Book is available \n";
    } else {
        out << book.getPatron()->getName() << "\n";
    }

    return out;
}

vector<shared_ptr<Patron>> Book::getHolds() const {
    LinkedQueue<shared_ptr<Patron>> holdQueueCopy = patronsOnHold;
    vector<shared_ptr<Patron>> patronHoldVector;

    while(!holdQueueCopy.isEmpty()){
        patronHoldVector.push_back(holdQueueCopy.peekFront());
        holdQueueCopy.dequeue();
    }
    return patronHoldVector;
}
