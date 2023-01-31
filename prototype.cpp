#include <iostream>
#include <string>
using namespace std;

class IPrototype {
  public:
    virtual IPrototype* Clone() = 0;
    virtual ~IPrototype() {}
};

class Phone : public IPrototype {
  public:
    Phone() {
      name = "Meta";
      cpu = "amd";
      price = 100;
    }
    Phone(const Phone& phone) {
      this->name = phone.name;
      this->cpu = phone.cpu;
      this->price = phone.price;
    }
    Phone* Clone() override {
      return new Phone(*this);
    }
    void Print() const {
      cout << "Name: " << name << endl
           << "Cpu:  " << cpu << endl
           << "Price:" << price << endl;
    }
    void SetName(const string& name) {
      this->name = name;
    }
    void SetPrice(int price) {
      this->price = price;
    }
  private:
    string name;
    string cpu;
    int price;
};

int main(void) {
  Phone* phone = new Phone();
  phone->Print();

  Phone* phone_clone = phone->Clone();
  phone_clone->Print();

  phone->SetName("Nova");
  phone->SetPrice(1000000);
  phone->Print();

  Phone* phone_clone2 = phone->Clone();
  phone_clone2->Print();

  delete phone;
  delete phone_clone;
  delete phone_clone2;
  return 0;
}