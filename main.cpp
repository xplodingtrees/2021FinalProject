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
    cout << "      20) Load Data" << endl;
    cout << "      21) Save Data" << endl;
    cout << "--------------------------------------" << endl;
    cout << "      99) Quit." << endl;
    cout << string(60, '=')  << endl;

    while (option < 1 || option >4){
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

    cout << "Enter Title: ";
    cin >> title;
    if(libPtr->searchBookTitle(title) != nullptr) {
        cout << "\n Book already added. Enter anything to continue.";
        cin >> title;
        return false;
    }
    cout << "\n Enter ISBN: ";
    cin >> isbn;
    cout << "\n Enter publication date: ";
    cin >> pubDate;
    cout << "\n Enter publisher: ";
    cin >> publisher;
    cout << "\n Enter page count: ";
    cin >> pageCount;
    shared_ptr<Book> aBook = make_shared<Book>(title, isbn, pubDate, publisher, pageCount);

    bool done = false;
    shared_ptr<Author> anAuthor;
    while(!done) {
        cout << "\n Please enter an author or 99 to finish";
        cin >> author;
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

void removeBook(const shared_ptr<Library>& lib, const string& title){
    if(lib->removeBook(title))
        cout << title << " has been removed from the library." << endl;
    else
        cout << title << " could not be removed from the library." << endl;
}

void addPatron(const shared_ptr<Library>& lib, const string& name, const string& address, const string& phoneNum){
    if (lib->addPatron(name, address, phoneNum)){
        cout << "Patron: " << name << " has been added to the library." << endl;
    }
    else{
        cout << "There was a problem adding this patron to the library." << endl;
    }
}

int main(){
    shared_ptr<Library> library = make_shared<Library>("Cool Library", "123 Sesame Street", "12 AM - 12:15 AM Mondays");
    string directory; //stores the data directory
    string title; //stores a book title

    int option = 0;

    while (option>=0){
        option = printMenu();
        switch (option) {
            case 1: // add book
                addBook(library);
                break;
            case 2: // list available books
                cout << endl << "Available books:" << endl;
                listAvailableBooks(library);
                break;
            case 3: // list checked out books
                break;
            case 4: // remove book by title
                cout << endl << "Enter title of the book to remove:" << endl;
                cin >> title;
                removeBook(library, title);
                break;
            case 5: // search book
                break;
            case 6: // add patron
                break;
            case 7: // list patrons
                break;
            case 8: // check out book
                break;
            case 9: // place hold on book
                break;
            case 10: // place book in drop box
                break;
            case 11: // check in books from drop box
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