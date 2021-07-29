#include "iostream"
#include "Book.h"
#include "Library.h"
#include "Author.h"
#include "Patron.h"

using namespace std;

int printMenu(){
    int option = 0;
    cout << "\n\n" << endl;
    cout << string(120, '=')  << endl;
    cout << "                    MAIN MENU   " << endl;
    cout << "------------------------------------------------" << endl;
    cout << "      1) Display Streaming Service  " << endl;
    cout << "      2) Checking existence of movie" << endl;
    cout << "      3) List Movie titles sorted   " << endl;
    cout << "      4) Search for movie           " << endl;
    cout << "                            99) Quit" << endl;
    cout << "------------------------------------------------" << endl;
    while (option < 1 || option >4){
        cout << "      Select your option [1-4/99]>> ";
        cin >> option;
        if (option == 99)
            return -1;
    }
    return option;
}

int getValidOption(){

}

int main(){
    int option = 0;
    string searchMovie;
    string pattern;
    while (option>=0){
        option = printMenu();
        switch (option) {
            case 1: // Display Students
                break;
            case 2: // Display Courses
                break;
            case 3: // Display Raw Records
                break;

            case 4: // Display Full Transcript
                break;
            default:
                cout<< "Invalid option...";
                break;
        }
    }
    cout << "Program Terminated." << endl;
    return 0;
}