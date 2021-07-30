#include "Library.h"

using namespace std;

Library::Library(){}

Library::Library(const string &name, const string &address, const string &hours)
        : name(name), address(address), hours(hours){

    shared_ptr<Comparator<shared_ptr<Book>>> bookComparator = make_shared<BookComparator>();
    bookIndex = make_shared<BinarySearchTree<shared_ptr<Book>>>(bookComparator);

    patrons = make_shared<LinkedList<shared_ptr<Patron>>>();
    books = make_shared<LinkedBag<shared_ptr<Book>>>();
    dropBox = make_shared<LinkedStack<shared_ptr<Book>>>();
    authors = make_shared<LinkedBag<Author>>();

}

Library::~Library() = default;


bool Library::addBook(shared_ptr<Book> &aBook) {
    bool added = false;
    aBook->setIsAvailable(true);
    if(books->add(aBook)) {
        added = bookIndex->add(aBook); // If book is added successfully, add it to the search tree.
    }
    return added;
}

bool Library::removeBook(const string& bookTitle) {
    bool removed = false;
    shared_ptr<Book> bookToRemove = searchBookTitle(bookTitle);
    if((bookToRemove != nullptr) && (bookToRemove->getIsAvailable()) && (books->remove(bookToRemove))) { //Checks to see if its null, then if its available, then finally if it is removed
        removed = bookIndex->remove(bookToRemove);// If book is removed from bag, remove it from the search tree
    }
    return removed;
}

bool Library::addPatron(string name, string address, string phoneNum) {
    shared_ptr<Patron> newPatron = make_shared<Patron>()
}

bool Library::checkOutBook(string phoneNum, string bookTitle) {
    //#Todo
    return false;
}

bool Library::setHold(string phoneNum, string bookTitle) {
    //#Todo
    return false;
}

bool Library::returnBook(string bookTitle) {
   shared_ptr<Book> returnedBook = searchBookTitle(bookTitle);
   bool returnVal;
   if(returnedBook == nullptr) {
       returnVal = false;
   } else {
       returnVal = dropBox->push(returnedBook); // Attempts to put the returnBook in dropbox. No need to modify anything else
   } // The library only needs to modify whats available when the book is restocked.
   return returnVal;
}

bool Library::checkInBook() {
    bool returnVal = true;
    if(dropBox->isEmpty()) {
        returnVal = false;
    } else {
        shared_ptr<Book> aBook = dropBox->peek();
        returnVal = dropBox->pop();

        if(aBook->isOnHold()) {
            returnVal = aBook->nextHold();//The next person on hold gets the book
        } else {
            aBook->setIsAvailable(true);// Book is now available
            aBook->setPatron(nullptr);
        }
    } // end of if/else

    return returnVal;

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

vector<shared_ptr<Book>> Library::availableBooks() {
    vector<shared_ptr<Book>> allBooks = books->toVector();
    vector<shared_ptr<Book>> booksAvailable;

    for(int i = 0; i < allBooks.size(); i++) {
        if(allBooks[i]->getIsAvailable()) {
            booksAvailable.push_back(allBooks[i]);// If book is avaqilable, add it to the list
        } // End iff
    } // End for
    return booksAvailable;
}

vector<shared_ptr<Book>> Library::checkedBooks() {
    vector<shared_ptr<Book>> allBooks = books->toVector();
    vector<shared_ptr<Book>> booksUnavailable;
    for(int i = 0; i < allBooks.size(); i++) {
        if(!allBooks[i]->getIsAvailable()) {
            booksUnavailable.push_back(allBooks[i]); //Adds only unavailable books to the vector
        } //end if
    }// end for
    return booksUnavailable;
}

shared_ptr<LinkedList<shared_ptr<Patron>>> Library::registeredPatrons() {
    return patrons;
}

vector<shared_ptr<Book>> Library::searchBookPattern(const string& searchTerm) {
    vector<shared_ptr<Book>> foundBooks;
    vector<shared_ptr<Book>> bookVector = books->toVector();
    string testTitle = searchTerm;

    transform(testTitle.begin(), testTitle.end(), testTitle.begin(), ::toupper);
    const regex txt_regex(testTitle);

    for(int i = 0; i < bookVector.size(); i++){
        string movieTitle = bookVector[i]->getTitle();
        transform(movieTitle.begin(), movieTitle.end(), movieTitle.begin(), ::toupper);

        if(regex_search(movieTitle, txt_regex)) {
            foundBooks.push_back(bookVector[i]);
        }
    }

    return foundBooks;
}


shared_ptr<Book> Library::searchBookTitle(const string& searchTerm) {
    for (const shared_ptr<Book>& aBook:this->books->toVector())
        if (aBook->getTitle() == searchTerm)
            return aBook;
    return nullptr;
}

shared_ptr<Patron> Library::searchPatron(const string& phoneNum) {
    for(int i = 1; i <= patrons->getLength(); i++) {
        if(patrons->getEntry(i)->getPhoneNum() == phoneNum) {
            return patrons->getEntry(i);
        }// end if
    } // end for
    return nullptr;
}