struct phoneObject {
  string name;
  string number;
  string nickname;
};

class PhoneBook {
  public:
    phoneObject phoneobj;

  private:
    void add(const string &name, const string &number, const string &nickname);
    string search(const string &input);
    void get_List();

}