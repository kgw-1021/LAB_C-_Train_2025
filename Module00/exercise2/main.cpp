
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct phoneObject {
    string name;
    string number;
    string nickname;
    bool isBookmarked = false;
};

class PhoneBook {
private:
    vector<phoneObject> phoneList;

public:
    void ReadPhoneBook();
    void SavePhoneBook();
    void SearchPhoneBook();
    void DisplayList();
    void ModifyList(const string& action);
    void addPhoneObject(const phoneObject& obj);
};

void PhoneBook::addPhoneObject(const phoneObject& obj) {
    phoneList.push_back(obj);
}
 
void PhoneBook::ReadPhoneBook() {
    ifstream file("phoneBook.csv");
    if (!file.is_open()) {
        cout << "No existing phoneBook.csv file. Starting fresh." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            phoneObject obj;
            obj.name = line.substr(0, pos1);
            obj.number = line.substr(pos1 + 1, pos2 - pos1 - 1);
            obj.nickname = line.substr(pos2 + 1, pos3 - pos2 - 1);
            obj.isBookmarked = line.substr(pos3 + 1) == "1";
            phoneList.push_back(obj);
        }
    }

    file.close();
}

void PhoneBook::SearchPhoneBook() {
    cout << "Enter What you search : ";
    string key;
    cin >> key;
    cout << "PhoneBook List:\n";
    cout << "| # |  Name  |  Phone Number  |  Nick Name  |" << endl;
    for (size_t i = 0; i < phoneList.size(); ++i) {
        if (phoneList[i].name.find(key) != string::npos) {
            cout << (i + 1) << ". "
                << phoneList[i].name 
                << phoneList[i].number
                << phoneList[i].nickname 
                << (phoneList[i].isBookmarked ? "★" : "")
                << endl;
        }
    }
    bool run = true;
    cout << "Press any button to go Menu.";
    int choice = getch();
    switch (choice)
    {
    default:
      break;
    }
    
}

void PhoneBook::SavePhoneBook() {
    ofstream file("phoneBook.csv");
    for (const auto& obj : phoneList) {
        file << obj.name << "," << obj.number << "," << obj.nickname << "," << (obj.isBookmarked ? "1" : "0") << endl;
    }
    file.close();
}

void PhoneBook::DisplayList() {
    cout << "PhoneBook List:\n";
    cout << "| # |      Name      |      Phone Number      |      Nick Name      |" << endl;
    for (size_t i = 0; i < phoneList.size(); ++i) {
        cout << "  " 
            << (i + 1) << ".      "
            << phoneList[i].name << "       "
            << phoneList[i].number << "           "
            << phoneList[i].nickname  << "           "
            << (phoneList[i].isBookmarked ? "★" : "")
            << endl;
    }
}

void PhoneBook::ModifyList(const string& action) {
    if (phoneList.empty()) {
        cout << "The phone book is empty.\n";
        return;
    }

    size_t currentIndex = 0;
    bool running = true;

    while (running) {
        system("clear");
        DisplayList();
        
        cout << "\033[" << (currentIndex + 1) << ";1H> "; 

        int key = getch();
        switch (key) {
        case 72: // Up key
            if (currentIndex > 0)
                --currentIndex;
            break;
        case 80: // Down key
            if (currentIndex < phoneList.size() - 1)
                ++currentIndex;
            break;
        case 13: // Enter key
            if (action == "delete") {
                phoneList.erase(phoneList.begin() + currentIndex);
                cout << "Item deleted successfully!\n";
            } else if (action == "bookmark") {
                phoneList[currentIndex].isBookmarked = true;
                cout << "Item bookmarked successfully!\n";
            }
            running = false;
            break;
        case 27: // ESC key
            running = false;
            break;
        }
    }
}

int Menu() {
  int input = getch();
  int notAllowedInput = 99;
  if (input != '1' && input != '2' && input != '3' && input != '4' &&
      input != '5')
    return notAllowedInput;
  else
    return input;
}

int main() {
    PhoneBook phonebook;
    phonebook.ReadPhoneBook();

    bool run = true;
    system("clear");
    while (run) {
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
            cin >> obj.name;
            cout << "Enter Number: ";
            cin >> obj.number;
            cout << "Enter Nickname: ";
            cin >> obj.nickname;
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
            cout << "Invalid input. Please try again." << endl;
        }
    }

    return 0;
}
