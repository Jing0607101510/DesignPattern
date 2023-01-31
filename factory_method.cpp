#include <iostream>
using namespace std;

class IPhone {
 public:
  virtual void Call() = 0;
  virtual ~IPhone() {}
};

class HWMate : public IPhone {
 public:
  void Call() override {
    cout << "HWMate Call" << endl;
  }
};

class HWNova : public IPhone {
 public:
  void Call() override {
    cout << "HWNova Call" << endl;
  }
};

class IFactory {
 public:
  virtual IPhone* CreatePhone() = 0;
  virtual ~IFactory() {}
};

class HWMateFactory : public IFactory {
 public:
  IPhone* CreatePhone() override {
    return new HWMate();
  }
};

class HWNovaFactory : public IFactory {
 public:
  IPhone* CreatePhone() override {
    return new HWNova();
  }
};

int main(void) {
  IFactory* meta_factory = new HWMateFactory();
  IPhone* meta_phone = meta_factory->CreatePhone();
  meta_phone->Call();
  delete meta_factory;
  delete meta_phone;

  IFactory* nova_factory = new HWNovaFactory();
  IPhone* nova_phone = nova_factory->CreatePhone();
  nova_phone->Call();
  delete nova_phone;
  delete nova_factory;
  return 0;
}