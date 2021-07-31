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
    authors = make_shared<LinkedBag<shared_ptr<Author>>>();

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

bool Library::addPatron(const string& name,const string& address,const string& phoneNum) {
    shared_ptr<Patron> newPatron = make_shared<Patron>(name, address, phoneNum);
    return patrons->insert(patrons->getLength()+1, newPatron);//Adds the new patron to the list
}

bool Library::checkOutBook(const string& phoneNum,const string& bookTitle) {
    shared_ptr<Patron> aPatron = searchPatron(phoneNum);
    shared_ptr<Book> aBook = searchBookTitle(bookTitle);
    if(aBook != nullptr && aPatron != nullptr && aBook->getIsAvailable()) {
        //If here, both the book and patron exist and have been found and the book is available
        aBook->setIsAvailable(false);
        aBook->setPatron(aPatron);
        return true;
    } else {
        return false;//One of the values given was nullptr
    }
}

bool Library::setHold(const string& phoneNum,const string& bookTitle) {
    shared_ptr<Patron> aPatron = searchPatron(phoneNum);
    shared_ptr<Book> aBook = searchBookTitle(bookTitle);
    if(aBook != nullptr && aPatron != nullptr) {
        //If here, both the book and patron exist and have been found
        return aBook->addHold(aPatron);
    } else {
        return false;//One of the values given was nullptr
    }
}

bool Library::returnBook(const string& bookTitle) {
   shared_ptr<Book> returnedBook = searchBookTitle(bookTitle);
   bool returnVal;
   if(returnedBook == nullptr || returnedBook->getIsAvailable()) {
       returnVal = false;
   } else {
       returnVal = dropBox->push(returnedBook); // Attempts to put the returnBook in dropbox. No need to modify anything else
   } // The library only needs to modify whats available when the book is restocked.
   return returnVal;
}

bool Library::checkInBook() {
    bool returnVal;
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

void Library::load(const string& directory) {
    string line;
    int count = 0; //holds line number
    string bookName; //holds current book name
    fstream readFile(directory); //read file
    int insertPoint = 1;
    bool endOfBookSection = false;

    //load patrons
    while(getline(readFile, line)){
        shared_ptr<Patron> newPatron = make_shared<Patron>();
        count++; //increment line count
        if (line.find('>') != string::npos){
            line = line.substr(2,line.length()); //trim string to just patron name
            newPatron->setName(line.substr(0, line.find(',')));
            line.erase(0,line.find(',')+1); //remove first section delimited in string
            newPatron->setAddress(line.substr(0, line.find(',')));
            line.erase(0,line.find(',')+1); //remove second section delimited in string
            newPatron->setPhoneNum(line.substr(0, line.find(',')));
            cout << endl;
            patrons->insert(insertPoint, newPatron);
            insertPoint++; //increment insert point index
        }// end if
        if (line.find("Books=") != string::npos){
            break;
        }// end if
    }//end while

    //load books
    shared_ptr<Book> newBook = make_shared<Book>();

    while(getline(readFile, line)){
        //shared_ptr<Book> newBook = make_shared<Book>();

        //check if a book section is ended and create new pointer for next book
        if(endOfBookSection){
            newBook = make_shared<Book>();
            endOfBookSection = false; //set end of book flag back to false
        }

        count++; //increment line count

        if (line.find('{') != string::npos){
            cout << endl;
            line = line.substr(0,line.length()-1); //trim string to just book name
            newBook->setTitle(line);
            bookIndex->add(newBook); //add the book to index
            books->add(newBook); //add to book list
            continue;
        }// end if

        //load isbn
        if (line.find("isbn=") != string::npos){
            getline(readFile, line);
            line = line.substr(2,line.length()); //trim string to just book isbn
            newBook->setIsbn(stoi(line)); //set book isbn
            continue;
        }// end if

        //load date
        if (line.find("date=") != string::npos){
            getline(readFile, line);
            line = line.substr(2,line.length()); //trim string to just book date
            newBook->setPubDate(line); //set book pubdate
            continue;
        }// end if

        //load publisher
        if (line.find("publisher=") != string::npos){
            getline(readFile, line);
            line = line.substr(2,line.length()); //trim string to just book publisher
            newBook->setPublisher(line);
            continue;
        }// end if

        //#TODO check this is functional
        //load status
        if (line.find("status=") != string::npos){
            getline(readFile, line);
            line = line.substr(2,line.length()); //trim string to just book status
            if(line == "1"){
                newBook->setIsAvailable(true);
            }
            else{
                newBook->setIsAvailable(true);
                line.erase(0,line.find(',')+1); //remove first section delimited in string

                //search patron and add to book
                newBook->setPatron(searchPatron(line));
            }//end if
            continue;
        }// end if

        //load authors
        if (line.find("authors=") != string::npos){
            while(true){
                getline(readFile, line);
                if(line.find("holds=") != string::npos){ //break if end of section found
                    break;
                }// end if
                line = line.substr(2,line.length()); //trim string to just book author
                shared_ptr<Author> newAuthor = make_shared<Author>(line); //create new author
                //cout << "adding author:" << line << ",to book:" << bookName << endl;
                //newAuthor->setName(line); //set new author name
                newBook->addAuthor(newAuthor); //add author to book
                authors->add(newAuthor); //add author to master author list

            }
        }// end if

        //load holds
        if (line.find("holds=") != string::npos){
            while(true){
                getline(readFile, line);
                if(line.find('}') != string::npos){ //break if end of section found
                    break;
                }
                line = line.substr(2,line.length()); //trim string to just patron phone
                //cout << "adding holds:" << line << ",to book:" << bookName << endl;
                shared_ptr<Patron> patronFound = searchPatron(line); //get patron by phone number and assign to patronFound
                newBook->addHold(patronFound); //add hold for book using found patron
            }
            continue;
        }// end if

        //end loop if bin section encountered
        if (line.find("Bin=") != string::npos){
            //end adding holds
            //cout << endl;

            //set end of booksection to true, to create a new pointer for next book
            endOfBookSection = true;

            //shared_ptr<Book> newBook = make_shared<Book>();
            break;
        }// end if
    }//end while

    //#TODO finish drop box load section
    //load drop box
    while(getline(readFile, line)){
        count++; //increment line count
        if (line.find('+') != string::npos){
            line = line.substr(2,line.length()); //trim string to just patron name
            //cout << "adding book to drop box:" << line << endl;
            //search bookindex for book, then add by name
            dropBox->push(searchBookTitle(line));
        }// end if
    }//end while
    readFile.close();
}

void Library::save(const string& directory) {

    ofstream writeFile(directory); //instantiate the output file stream object
    vector<shared_ptr<Book>> bookVector; //vector stores books in library

    //check if books empty before adding to vector
    if(books->getCurrentSize() > 0){
        bookVector = books->toVector(); //load book vector
    }

    shared_ptr<LinkedStack<shared_ptr<Book>>> dropBoxCopy = dropBox; //make a copy of drop box, save shouldn't pop actual

    //populate patrons section
    writeFile << "Patrons=\n";
    for(int index = 0; index < patrons->getLength(); index++){
        //write patron data, delimit with comma
        writeFile << "\t" << ">" << patrons->getEntry(index)->getName() << ","
            << patrons->getEntry(index)->getAddress() << "," << patrons->getEntry(index)->getPhoneNum() << "\n";
    }//end for

    //populate book section
    writeFile << "Books=\n";
    //cycle through books and add to file
    for(int index = 0; index < bookVector.size(); index++){
        //vector of book authors used to populate author section
        vector<shared_ptr<Author>> bookAuthors = bookVector.at(index)->getAuthors();

        writeFile << bookVector.at(index)->getTitle() << "{" << "\n"; //write book title

        //add isbn
        writeFile << "\tisbn=" << "\n";
        writeFile << "\t\t" << bookVector.at(index)->getIsbn() << "\n";

        //add publish date
        writeFile << "\tdate=" << "\n";
        writeFile << "\t\t" << bookVector.at(index)->getPubDate() << "\n";

        //add publisher
        writeFile << "\tpublisher=" << "\n";
        writeFile << "\t\t" << bookVector.at(index)->getPublisher() << "\n";

        //write status
        //#TODO check patron saves correct
        writeFile << "\tstatus=\n";
        if(bookVector.at(index)->getIsAvailable()){
            writeFile << "\t\t" << to_string(bookVector.at(index)->getIsAvailable()) <<  "\n";
        }
        else{
            //if unavailable, write 0 and add delimit+patron phoneNum
            writeFile << "\t\t" << to_string(bookVector.at(index)->getIsAvailable())
                << "," << bookVector.at(index)->getPatron()->getPhoneNum() << "\n";
        }


        //copy all the book authors
        //#TODO check author section properly implemented once getAuthors is defined
        writeFile << "\tauthors=" << "\n";
        for(int index2 = 0; index2 < bookAuthors.size(); index2++){
            writeFile << "\t\t" << bookAuthors.at(index2)->getName() << "\n";
        }//end for

        //write holds
        writeFile << "\tholds=\n";

        //#TODO finish holds save section
        //check if holds exist
        if(bookVector.at(index)->isOnHold()){ //add patron phone number to hold section
            //grab the patrons on hold for book
            vector<shared_ptr<Patron>> patronHoldsVector = bookVector.at(index)->getHolds();
            for(int index3 = 0; index3 < patronHoldsVector.size(); index3++){
                writeFile << "\t\t" << patronHoldsVector.at(index3)->getPhoneNum() << "\n"; //write patron phone number
            }//end for

        }
        else{
            //can probably omit this part eventually
            writeFile << "\t\tnone\n";
        }// end if

        writeFile << "}\n";
    }//end for

    //populate bin section
    writeFile << "Bin=\n";
    //cycle through drop box and save book title to file
    while(!dropBoxCopy->isEmpty()){
        writeFile << "\t+" << dropBoxCopy->peek()->getTitle() << endl;
        dropBoxCopy->pop();
    }//end while
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
            booksAvailable.push_back(allBooks[i]);// If book is available, add it to the list
        } // End if
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
        }//end if
    }//end for

    return foundBooks;
}


shared_ptr<Book> Library::searchBookTitle(const string& searchTerm) {
    for (const shared_ptr<Book>& aBook:this->books->toVector()){
        if (aBook->getTitle() == searchTerm)
            return aBook;
    }
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

shared_ptr<Author> Library::searchAuthor(const string& name) {
    for (const shared_ptr<Author>& anAuthor:this->authors->toVector())
        if (anAuthor->getName() == name)
            return anAuthor;
    return nullptr;
}

shared_ptr<Author> Library::createAuthor(const string& name){
    //check if author exists, if true return existing, else create and return new author
    shared_ptr<Author> returnAuthor;
    returnAuthor = searchAuthor(name);

    if(returnAuthor == nullptr){
        returnAuthor = make_shared<Author>(name);
    }

    return returnAuthor;


}