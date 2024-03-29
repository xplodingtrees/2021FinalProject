#include "iostream"
#include "Book.h"
#include "Library.h"
#include "Author.h"
#include "Patron.h"

using namespace std;

/**
* Prints menu options and takes user input to determine option
* @return menu option
*/
int printMenu(){
    int option = 0;
    cout << string(60, '=')  << endl;
    cout << "                    CSE LIBRARY MAIN MENU   " << endl;
    cout << string(60, '=')  << endl;
    cout << "      1) Book: Add" << endl;
    cout << "      2) Book: List Available" << endl;
    cout << "      3) Book: List Checked Out" << endl;
    cout << "      4) Book: Remove by Title" << endl;
    cout << "      5) Book: Search" << endl;
    cout << "--------------------------------------" << endl;
    cout << "      6) Patrons: Add" << endl;
    cout << "      7) Patrons: List" << endl;
    cout << "--------------------------------------" << endl;
    cout << "      8) Check Out Book" << endl;
    cout << "      9) Place Hold" << endl;
    cout << "      10) Place Book to Drop Box" << endl;
    cout << "      11) Check In Books From Drop Box" << endl;
    cout << "--------------------------------------" << endl;
    cout << "      20) Load Data (Doesn't work, but we tried)" << endl;
    cout << "      21) Save Data (Doesn't Work, but we tried)" << endl;
    cout << "--------------------------------------" << endl;
    cout << "      99) Quit." << endl;
    cout << string(60, '=')  << endl;

    while (!((option >= 1 && option <= 11) || option == 21 || option == 20)){
        cout << "      Enter your option [1-11 / 20 / 21 / 99]:";
        cin >> option;
        if (option == 99)
            return -1;
    }
    return option;
}

int getValidOption(){
    return 1;
}

/**
* Checks which file system is used and appends directory with filename accordingly
* @param directory
* @return file path
*/
string processDirectory(string directory){
    //check if windows/linux, then append filename to given directory string
    if(directory.substr(1,1) == ":"){
        //if last char is a separator, remove it
        if(directory.substr(directory.length()-1,directory.length()) == "\\"){
            directory = directory.substr(0, directory.length()-1);
        }
        //add filename to directory
        directory = directory + "\\libraryData";
    }
    else{
        //check if windows/linux, then append filename to given directory string
        if(directory.substr(directory.length()-1,directory.length()) == "/"){
            directory = directory.substr(0, directory.length()-1);
        }
        //add filename to directory
        directory = directory + "/libraryData";
    }
    return directory;
}

bool addBook(shared_ptr<Library> &libPtr) {
    string title;
    int isbn;
    string pubDate;
    string publisher;
    int pageCount;
    string author;

    string input;

    cout << "Enter Title: ";
    cin.ignore();
    if (!getline(cin, input))
    {
        cout << "LINE READ ERROR ABORT ABORT";
    }
    title = input;

    if(libPtr->searchBookTitle(title) != nullptr) {
        cout << "\n Book already added. Enter anything to continue.";
        cin >> title;
        return false;
    }

    cout << "\n Enter ISBN (integer): ";
    if (!getline(cin, input))
    {
        cout << "LINE READ ERROR ABORT ABORT";
    }
    isbn = stoi(input);

    cout << "\n Enter publication date: ";
    if (!getline(cin, input))
    {
        cout << "LINE READ ERROR ABORT ABORT";
    }
    pubDate = input;

    cout << "\n Enter publisher: ";
    if (!getline(cin, input))
    {
        cout << "LINE READ ERROR ABORT ABORT";
    }
    publisher = input;

    cout << "\n Enter page count (integer): ";
    if (!getline(cin, input))
    {
        cout << "LINE READ ERROR ABORT ABORT";
    }
    pageCount = stoi(input);

    shared_ptr<Book> aBook = make_shared<Book>(title, isbn, pubDate, publisher, pageCount);

    bool done = false;
    shared_ptr<Author> anAuthor;
    while(!done) {
        cout << "\n Please enter an author or 99 to finish: ";
        if (!getline(cin, input))
        {
            cout << "LINE READ ERROR ABORT ABORT";
        }
        author = input;
        if(author == "99") {
            done = true;
        } else {
            anAuthor = libPtr->createAuthor(author);
            aBook->addAuthor(anAuthor);
        }
    }

    return libPtr->addBook(aBook);

}

void listAvailableBooks(const shared_ptr<Library> lib){
    vector<shared_ptr<Book>> availableBooks = lib->availableBooks();

    for(int index = 0; index < availableBooks.size(); index++){
        cout << availableBooks.at(index)->getTitle() << endl;
    }
}

void listUnavailableBooks(const shared_ptr<Library> lib){
    vector<shared_ptr<Book>> unavailableBooks = lib->checkedBooks();

    for(int index = 0; index < unavailableBooks.size(); index++){
        cout << unavailableBooks.at(index)->getTitle() << endl;
    }
}

void removeBook(const shared_ptr<Library>& lib, const string& title){
    if(lib->removeBook(title))
        cout << title << " has been removed from the library." << endl;
    else
        cout << title << " could not be removed from the library. It is either unavailable or does not exist." << endl;
}

void searchForBook(shared_ptr<Library>& lib, const string& title) {
    cout << endl << "#####################################################################" << endl;
    cout << endl << "####################      SEARCHING BOOKS      ######################" << endl << endl;

    vector<shared_ptr<Book>> matchingBooks = lib->searchBookPattern(title);

    if(matchingBooks.size() == 0) {
        cout << "No Matching books found." << endl;
    }

    for(shared_ptr<Book> aBook: matchingBooks) {
        cout << *aBook << endl << endl << endl;
    }
}

void addPatron(const shared_ptr<Library>& lib, const string& name, const string& address, const string& phoneNum){
    if (lib->addPatron(name, address, phoneNum)){
        cout << "Patron: " << name << " has been added to the library." << endl;
    }
    else{
        cout << "There was a problem adding this patron to the library." << endl;
    }
}

void listPatrons(const shared_ptr<Library>& lib){
    cout << string(60, '-')  << endl;
    cout << "\n" << lib->registeredPatrons()->getLength() << " patrons are registered in the library" << endl;
    cout << "\n\nPatron List:\n";
    for(int index = 1; index <= lib->registeredPatrons()->getLength(); index++){
        cout << endl << "\t" << "Name: " << lib->registeredPatrons()->getEntry(index)->getName() << endl;
        cout << "\t" << "Address: " << lib->registeredPatrons()->getEntry(index)->getAddress() << endl;
        cout << "\t" << "Phone Number: " << lib->registeredPatrons()->getEntry(index)->getPhoneNum() << endl << endl;
    }
    cout << string(60, '-')  << endl;
}

void placeBookInDropBox(const shared_ptr<Library>& lib, const string& title){
    if(lib->returnBook(title)){
        cout << title << " has been placed in the drop box.";
    }
    else{
        cout << title << " could not be placed in the drop box.";
    }
}

void checkInBooks(const shared_ptr<Library>& lib){
    if(lib->checkInBook()){
        cout << "Checked in a book.";
    }
    else{
        cout << "There was a problem checking in book from the drop box. It may be empty.";
    }
}

void checkOutBook(const shared_ptr<Library>& lib, const string& title, const string& phoneNum){
    if(lib->checkOutBook(phoneNum, title)){
        cout << title << " has been successfully checked out to " << lib->searchPatron(phoneNum)->getName() << endl;
    }
    else{
        cout << title << " could not be checked out." << endl;
    }
}

void placeBookOnHold(const shared_ptr<Library>& lib, const string& title, const string& phoneNum){
    if(lib->setHold(phoneNum, title)){
        cout << title << " has been successfully placed on hold for " << lib->searchPatron(phoneNum)->getName() << endl;
    }
    else{
        cout << title << " could not be placed on hold." << endl;
    }
}

int main(){
    shared_ptr<Library> library = make_shared<Library>("Cool Library", "123 Sesame Street", "12 AM - 12:15 AM Mondays");
    string directory; //stores the data directory
    string title; //stores a book title
    string patronName; //stores a patron name
    string patronAddress; //stores a patron address
    string patronNum; //stores a patron phone number

    int option = 0;

    while (option>=0){
        option = printMenu();
        switch (option) {
            case 1: // add book
                addBook(library);
                break;
            case 2: // list available books
                cout << endl << "Available books: " << endl;
                listAvailableBooks(library);
                break;
            case 3: // list checked out books
                cout << endl << "Unavailable books: " << endl;
                listUnavailableBooks(library);
                break;
            case 4: // remove book by title
                cout << endl << "Enter title of the book to remove: ";
                cin.ignore();
                getline(cin, title);
                removeBook(library, title);
                break;
            case 5: // search book
                cout << endl << "Enter book name by title: ";
                cin.ignore();
                getline(cin, title);
                cout << endl;
                searchForBook(library, title);
                break;
            case 6: // add patron
                cout << endl << "Creating a new patron:\n";
                cout << "Enter name:";
                cin.ignore();
                getline(cin, patronName);
                cout << "\nEnter address:";
                getline(cin, patronAddress);
                cout << "\nEnter phone number:";
                getline(cin, patronNum);
                addPatron(library, patronName, patronAddress, patronNum);
                break;
            case 7: // list patrons
                listPatrons(library);
                break;
            case 8: // check out book
                cout << endl << "Checking out a book...\n";
                cout << "Enter book title:";
                cin.ignore();
                getline(cin, title);
                cout << "Enter patron phone number:";
                getline(cin, patronNum);
                checkOutBook(library, title, patronNum);
                break;
            case 9: // place hold on book
                cout << "Placing hold on book..." << endl;
                cout << "Enter book title:";
                cin.ignore();
                getline(cin, title);
                cout << "Enter patron phone number:";
                getline(cin, patronNum);
                placeBookOnHold(library, title, patronNum);
                break;
            case 10: // place book in drop box
                cout << endl << "Enter dropped off book name: ";
                cin.ignore();
                getline(cin, title);
                placeBookInDropBox(library, title);
                break;
            case 11: // check in books from drop box
                cout << endl << "Checking in books from the drop box... " << endl;
                checkInBooks(library);
                break;
            case 20: // load data
                cout << "Enter the absolute library data file path to load from (do not include filename):";
                cin >> directory;
                cout << endl;
                library->load(processDirectory(directory));
                break;
            case 21: // save data
                cout << "Enter the absolute library data file path to save to (do not include filename):";
                cin >> directory;
                cout << endl;
                library->save(processDirectory(directory));
                break;
            case -1: // exit
                return 0;
            default:
                cout<< "Invalid option...";
                break;
        }
        cout << "\n\n" << endl;
    }
    return 0;
}