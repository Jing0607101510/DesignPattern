#include <iostream>
#include <string>
#include <mutex>
using namespace std;

// 静态局部变量
class Phone {
  private:
    Phone() {
      name = "Meta";
      price = 100;
    }

    string name;
    int price;
  public:
    static Phone& GetPhoneInstance()  {
      static Phone phone;
      return phone;
    }
    void Print() {
      cout << "Name: " << name << endl
           << "Price:" << price << endl << endl;
    }
};

mutex mtx;

// 静态类成员指针，双检查锁；但是有缺陷
class Charge {
  private:
    Charge() {
      price = 10;
    }
    int price;
    static Charge* charge;
  public:
    static Charge& GetChargeInstance() {
      if (charge == nullptr) {
        unique_lock<mutex> lock(mtx);
        if (charge == nullptr) {
          charge = new Charge();
        }
      }
      return *charge;
    }
    void Print() {
      cout << "Price:" << price << endl << endl;
    }
};

Charge* Charge::charge = nullptr;

// 非懒汉模式
class PhoneCase {
  private:
    PhoneCase() {
      name = "case";
    }
    string name;
    static PhoneCase* phone_case;
  public:
    static PhoneCase& GetPhoneCaseInstance() {
      return *phone_case;
    }
    void Print() {
      cout << "Name: " << name << endl << endl;
    }
};

PhoneCase* PhoneCase::phone_case = new PhoneCase();

int main(void) {
  Phone& phone = Phone::GetPhoneInstance();
  phone.Print();
  Charge& charge = Charge::GetChargeInstance();
  charge.Print();
  PhoneCase& phone_case = PhoneCase::GetPhoneCaseInstance();
  phone_case.Print();
  delete &charge;
  delete &phone_case;
  return 0;
}