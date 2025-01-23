#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>

using namespace std;

struct phoneObject {
  string name;
  string number;
  string nickname;
};

class PhoneBook {
  private:
    phoneObject phoneobj;
    vector <phoneObject> phoneList;

  public:
    
    void PhonenumberADD();

    void PhoneNumberSearch();

    void phoneNumberRemove();

    void phoneNumberBookmark();

    void ReadPhoneBook();

    void get_List();

};

void PhoneBook::PhonenumberADD(){
  cout << "ADD" << endl;
}

void PhoneBook::PhoneNumberSearch(){
  cout << "Search" << endl;
}

void PhoneBook::phoneNumberRemove(){
  cout << "Remove" << endl;
}  

void PhoneBook::phoneNumberBookmark(){
  cout << "BookMark" << endl;
}

void PhoneBook::ReadPhoneBook(){
  cout << "Read " << endl;
  ifstream file("phoneBook.csv")

  getline(file, line);

}

void PhoneBook::get_List() {
}