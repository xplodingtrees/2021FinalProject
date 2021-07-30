#include "Library.h"

using namespace std;

Library::Library(){}

Library::Library(const string &name, const string &address, const string &hours)
        : name(name), address(address), hours(hours){

    shared_ptr<Comparator<shared_ptr<Book>>> bookComparator = make_shared<BookComparator>();
    bookIndex = make_shared<BinarySearchTree<shared_ptr<Book>>>(bookComparator);

    patrons = make_shared<LinkedList<shared_ptr<Patron>>>();
    books = make_shared<LinkedList<shared_ptr<Book>>>();
    booksUnavailable = make_shared<LinkedList<shared_ptr<Book>>>();
    booksAvailable = make_shared<LinkedList<shared_ptr<Book>>>();
    dropBox = make_shared<LinkedStack<shared_ptr<Book>>>();
}

Library::~Library() {}

bool Library::addBook(shared_ptr<Book> aBook) {
    bookIndex->add(aBook);
}

bool Library::removeBook(string bookTitle) {
    //#TODO removeBooks
    //bookIndex->inorderTraverse();
    return true;
}

bool Library::addPatron(string name, string address, string phoneNum) {
    //#TODO addpatron
    //patrons->insert();
    return true;
}

bool Library::checkOutBook(string phoneNum, string bookTitle) {
    return false;
}

bool Library::setHold(string phoneNum, string bookTitle) {
    return false;
}

bool Library::returnBook(string bookTitle) {
    for(int index = 0; index < books->getLength(); index++){
        if(books->getEntry(index)->getTitle() == bookTitle){
            dropBox->push(books->getEntry(index));
            break;
        }
    }
}

bool Library::checkInBooks() {
    while(!dropBox->isEmpty()){
        dropBox->peek()->setIsAvailable();
    }
}

void Library::load(string directory) {

    string line;
    int posMarker = 0; //holds a position in file
    int bookCount = 0; //counter used to track book count/index
    int count = 0; //holds line number
    string bookName; //holds current book name
    fstream readFile(directory); //read file

    //load patrons
    while(getline(readFile, line)){
        count++; //increment line count
        if (line.find(">") != string::npos){
            line = line.substr(2,line.length()); //trim string to just patron name
            cout << "adding patron:" << line << endl;
        }
        if (line.find("Books=") != string::npos){
            break;
        }
    }

    //load books
    while(getline(readFile, line)){
        count++; //increment line count

        if (line.find("{") != string::npos){
            cout << endl;
            line = line.substr(0,line.length()-1); //trim string to just book name
            cout << "adding book " << bookCount << ":" << line << endl;
            bookName = line; //set current book
            bookCount++;
            continue;
        }
        if (line.find("}") != string::npos){
            //cout << "end of book " << bookCount << endl;
            posMarker = count;
            continue;
        }
        //mark author position
        if (line.find("authors=") != string::npos){
            posMarker = count;
            continue;
        }
        //mark status position
        if (line.find("status=") != string::npos){
            posMarker = -1;
            continue;
        }
        if (line.find("holds=") != string::npos){
            posMarker = 0;
            continue;
        }
        if (line.find("Bin=") != string::npos){
            //end adding patrons
            cout << endl;
            break;
        }
        //if in author position, add authors to current book
        if (count > posMarker && posMarker > 0){
            //add authors to book
            line = line.substr(2,line.length()); //trim string to just book name
            cout << "adding author:" << line << ",to book:" << bookName << endl;
            continue;
        }
        //if in status position, add status to current book
        if(posMarker == -1){
            //add status to book
            line = line.substr(2,line.length()); //trim string to just book name
            cout << "adding status:" << line << ",to book:" << bookName << endl;
            continue;
        }
        //if in holds position, add holds to current book
        if(posMarker == 0){
            //add status to book
            line = line.substr(2,line.length()); //trim string to just book name
            cout << "adding hold:" << line << ",to book:" << bookName << endl;
            continue;
        }
    }

    //load drop box
    while(getline(readFile, line)){
        count++; //increment line count
        if (line.find('+') != string::npos){
            line = line.substr(2,line.length()); //trim string to just patron name
            cout << "adding book to drop box:" << line << endl;
        }
    }
    readFile.close();
}

void Library::save(string directory) {
    //temp test arrays
    string patrons[3] = {"patron1", "patron2", "patron3"};
    string dropbox[3] = {"book1", "book2"};
    string books[3][2] =  {{"b1author1", "b1author2"}, {"b2author1", "b2author2"}, {"b3author1", "b3author2"}};

    string writeFileAddress = directory;

    ofstream writeFile(writeFileAddress);

    //populate patrons section
    writeFile << "Patrons=\n";
    for(int index = 0; index < 3; index++){
        writeFile << "\t" << ">" << patrons[index] << "\n";
    }

    //populate book section
    writeFile << "Books=\n";
    //cycle through books and add to file
    for(int index = 0; index < 3; index++){
        writeFile << "BOOKNAME" << "{" << "\n";
        //copy all the book authors
        writeFile << "\tauthors=" << "\n";
        for(int index2 = 0; index2 < 2; index2++){
            writeFile << "\t\t" << books[index][index2] << "\n";
        }

        //write status
        writeFile << "\tstatus=\n";

        //if book available
        //else if book checked out
        //else book is in bin
        writeFile << "\t\tavailable\n";

        //write holds
        writeFile << "\tholds=\n";

        //if there are patrons on hold, add to file
        //if stack empty, add empty flag instead
        writeFile << "\t\tpatron1\n";

        writeFile << "}\n";
    }

    //populate bin section
    writeFile << "Bin=\n";
    //cycle through drop box and add to file
    for(int index = 0; index < 2; index++){
        writeFile << "\t+" << dropbox[index] << endl;
    }

    //check for extension, remove
    cout << "Library data saved to " << directory << endl;
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

shared_ptr<LinkedList<shared_ptr<Book>>> Library::availableBooks() {
    return booksAvailable;
}

shared_ptr<LinkedList<shared_ptr<Book>>> Library::checkedBooks() {
    return booksUnavailable;
}

shared_ptr<LinkedList<shared_ptr<Patron>>> Library::registeredPatrons() {
    return patrons;
}

vector<Book> Library::searchBooks(string searchTerm) {
    //#TODO searchbooks
    return vector<Book>();
}