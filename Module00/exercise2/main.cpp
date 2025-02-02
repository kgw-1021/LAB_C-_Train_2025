#include "phoneBook.hpp"

using namespace std;

int main() {
    PhoneBook phonebook;
    phonebook.ReadPhoneBook();

    bool run = true;
    system("clear");
    while (run) {
        phonebook.SortPhoneBook();
          cout << " Please choose what to do!" << endl;
          cout << " | 1.Add Phone number  | 2.Search Phone number | 3.Remove Phone "
          "number | 4.Bookmark Phone number | 5.Exit Program |" 
          << endl;
        phonebook.DisplayList();
        int choice = Menu();
        switch (choice) {
        case '1': {
            phoneObject obj;
            cout << "Enter Name: ";
            getline(cin, obj.name);
            cout << "Enter Number: ";
            getline(cin, obj.number);
            cout << "Enter Nickname: ";
            getline(cin, obj.nickname);
            obj.isBookmarked = false;
            phonebook.addPhoneObject(obj);
            cout << "Phone number added successfully!" << endl;
            system("clear");
            break;
        }
        case '2':
            phonebook.SearchPhoneBook();
            system("clear");
            break;
        case '3':
            phonebook.ModifyList("delete");
            system("clear");
            break;
        case '4':
            phonebook.ModifyList("bookmark");
            system("clear");
            break;
        case '5':
            phonebook.SavePhoneBook();
            system("clear");
            run = false;
            break;
        default:
            system("clear");
            cout << "Invalid input. Please try again." << endl << endl;
        }
    }

    return 0;
}
