#include <iostream>
using namespace std;

class IPhone {
  public:
    virtual void Call() = 0;
    virtual ~IPhone() {}
};

class MetaPhone : public IPhone {
  public:
    void Call() override {
      cout << "Meta Call" << endl;
    }
};

class NovaPhone : public IPhone {
  public:
    void Call() override {
      cout << "Nova Call" << endl;
    }
};

class ICharge {
  public:
    virtual void Charge() = 0;
    virtual ~ICharge() {}
};

class MetaCharge : public ICharge {
  public:
    void Charge() override {
      cout << "Meta Charge" << endl;
    }
};

class NovaCharge : public ICharge {
  public:
    void Charge() override {
      cout << "Nova Charge" << endl;
    }
};

class IFactory {
  public:
    virtual IPhone* CreatePhone() = 0;
    virtual ICharge* CreateCharge() = 0;
    virtual ~IFactory() {}
};

class MetaFactory : public IFactory {
  public:
    IPhone* CreatePhone() override {
      return new MetaPhone();
    }
    ICharge* CreateCharge() override {
      return new MetaCharge();
    }
};

class NovaFactory : public IFactory {
  public:
    IPhone* CreatePhone() override {
      return new NovaPhone();
    }
    ICharge* CreateCharge() override {
      return new NovaCharge();
    }
};

int main(void) {
  IFactory* meta_factory = new MetaFactory();
  IPhone* meta_phone = meta_factory->CreatePhone();
  ICharge* meta_charge = meta_factory->CreateCharge();
  meta_phone->Call();
  meta_charge->Charge();
  delete meta_factory;
  delete meta_phone;
  delete meta_charge;

  IFactory* nova_factory = new NovaFactory();
  IPhone* nova_phone = nova_factory->CreatePhone();
  ICharge* nova_charge = nova_factory->CreateCharge();
  nova_phone->Call();
  nova_charge->Charge();
  delete nova_factory;
  delete nova_phone;
  delete nova_charge;
  return 0;
}