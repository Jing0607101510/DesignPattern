#include <set>
#include <iostream>
using namespace std;

class AbstractCustomer {
  public:
    virtual bool IsNull() const = 0;
    virtual string GetName() const = 0;
    virtual ~AbstractCustomer() {}
  protected:
    string name;
};

class RealCustomer : public AbstractCustomer{
  public:
    RealCustomer(const string& name) {
      this->name = name;
    }
    bool IsNull() const {
      return false;
    }
    string GetName() const {
      return name;
    }

};

class NullCustomer : public AbstractCustomer {
  public:
    bool IsNull() const {
      return true;
    }
    string GetName() const {
      return "Null Object";
    }
};

class CustomerFactory {
  static set<string> names;
  public:
  static AbstractCustomer* GetCustomer(const string& name) {
    if (names.find(name) != names.end()) {
      return new RealCustomer(name);
    } else {
      return new NullCustomer();
    }
  }
};

set<string> CustomerFactory::names = {
  "Rob",
  "Joe",
};

int main(void) {
  AbstractCustomer* customer = CustomerFactory::GetCustomer("Rob");
  AbstractCustomer* customer2 = CustomerFactory::GetCustomer("AAA");
  cout << customer->GetName() << endl;
  cout << customer2->GetName() << endl;
  delete customer;
  delete customer2;
  return 0;
}