#include <iostream>
#include <string.h>

using namespace std;

class myString {
public:
  string str;
  string cmd;
  string cmd_opt;
  void convert2upper(const string &input);
  void convert2lower(const string &input);
};

void myString::convert2upper(const string &input) {
  this->str = input;
  for (int i = 0; i < this->str.length(); i++) {
    if (this->str[i] >= 97 && this->str[i] <= 122) // a ~ z
      this->str[i] = this->str[i] - 32;
  }
}

void myString::convert2lower(const string &input) {
  this->str = input;
  for (int i = 0; i < this->str.length(); i++) {
    if (this->str[i] >= 65 && this->str[i] <= 90) // A ~ Z
      this->str[i] = this->str[i] + 32;
  }
}

int main(int argc, char *argv[]) {
  myString str;
  str.cmd = argv[1];
  str.cmd_opt = argv[2];

  for (int i = 3; i < argc; i++) {
    str.str += argv[i];
    str.str += " ";
  }

  if (str.cmd == "convert") {
    if (str.cmd_opt == "up")
      str.convert2upper(str.str);
    else if (str.cmd_opt == "down")
      str.convert2lower(str.str);
    else {
      cerr << "Unknown command option: " << str.cmd_opt << endl;
      return 1;
    }
  } else {
    cerr << "Unknown command: " << str.cmd << endl;
    return 1;
  }

  cout << "Output : " << str.str << endl;
  return 0;
}