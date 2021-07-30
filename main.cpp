#include "iostream"
#include "Book.h"
#include "Library.h"
#include "Author.h"
#include "Patron.h"

using namespace std;

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
* @return list of available books
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

int main(){
    shared_ptr<Library> library = make_shared<Library>();
    string directory;
    //directory = "C:\\Users\\ocelo\\Desktop\\Library";
    int option = 0;

    while (option>=0){
        option = printMenu();
        switch (option) {
            case 1: // add book
                break;
            case 2: // list available books
                break;
            case 3: // list checked out books
                break;
            case 4: // remove book by title
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
                cout << "Enter the absolute library data file path (do not include filename):";
                cin >> directory;
                cout << endl;
                library->load(processDirectory(directory));
                break;
            case 21: // save data
                cout << "Enter the absolute library data file path (do not include filename):";
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