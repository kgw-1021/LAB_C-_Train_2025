#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <signal.h>

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
    void SortPhoneBook();
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
        ofstream newFile("phoneBook.csv");
        newFile.close();
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
    getline(cin, key);
    system("clear");
    cout << "Search Result :" << endl;
    cout << "|  #  |      Name      |    Phone Number    |    Nick Name    |  Book Mark  |" << endl;
    for (size_t i = 0; i < phoneList.size(); ++i) {
        if (phoneList[i].name.find(key) != string::npos) {
            cout << "| " << setw(2) << right << (i + 1) << ". " << "| "
                << setw(15) << left << phoneList[i].name << "| "
                << setw(19) << left << phoneList[i].number << "| "
                << setw(16) << left << phoneList[i].nickname  << "|      "
                << (phoneList[i].isBookmarked ? "★" : " ") << "      |"
                << endl;
        }
    }
    bool run = true;

    cout << "Press ESC to go Menu.";    
    while (run) {

      int choice = getch();

      switch (choice)
      {
      case 27:    // ESC -> 27 (ASCII)
        run = false;
        break;
      default:
        break;
      }
    }
}

void PhoneBook::SortPhoneBook() {
    sort(phoneList.begin(), phoneList.end(), [](const phoneObject &a, const phoneObject &b) {
        return a.isBookmarked > b.isBookmarked;
    });
}

void PhoneBook::SavePhoneBook() {
    ofstream file("phoneBook.csv");
    for (const auto& obj : phoneList) {
        file << obj.name << "," << obj.number << "," << obj.nickname << "," << (obj.isBookmarked ? "1" : "0") << endl;
    }
    file.close();
}

void PhoneBook::DisplayList() {
    cout << "PhoneBook List :" << endl;
    cout << "|  #  |      Name      |      Phone Number      |    Nick Name    |  Book Mark  |" << endl;
    for (size_t i = 0; i < phoneList.size(); ++i) {
        cout << "| " << setw(2) << right << (i + 1) << ". " << "| "
            << setw(15) << left << phoneList[i].name << "| "
            << setw(23) << left << phoneList[i].number << "| "
            << setw(16) << left << phoneList[i].nickname  << "|      "
            << (phoneList[i].isBookmarked ? "★" : " ") << "      |"
            << endl;
    }
}

void PhoneBook::ModifyList(const string& action) {
    system("clear");
    if (phoneList.empty()) {
        cout << "The phone book is empty." << endl;
        return;
    }

    DisplayList();
    cout << "Enter the number to " << action << ": ";
    int index;
    cin >> index;
    cin.ignore();

    if (index < 1 || index > static_cast<int>(phoneList.size())) {
        cout << "Invalid number. Returning to menu." << endl;
        return;
    }

    --index;

    if (action == "delete") {
        phoneList.erase(phoneList.begin() + index);
        cout << "Phone Number deleted successfully!\n";
    } else if (action == "bookmark") {
        phoneList[index].isBookmarked = true;
        cout << "Phone Number bookmarked successfully!\n";
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