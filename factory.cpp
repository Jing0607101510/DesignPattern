#include <iostream>
using namespace std;

// 简单工厂
class IPhone {
  public:
    virtual void Call() = 0;
    virtual void TakePicture() = 0;
    virtual void SendMessage() = 0;
    virtual ~IPhone() {};
};

class HWMate : public IPhone {
  public:
    void Call() override {
      cout << "HWMate Call" << endl;
    }
    void TakePicture() override {
      cout << "HWMate TakePicture" << endl;
    }
    void SendMessage() override {
      cout << "HWMate SendMessage" << endl;
    }
};

class HWNova : public IPhone {
  public:
    void Call() override {
      cout << "HWNova Call" << endl;
    }
    void TakePicture() override {
      cout << "HWNova TakePicture" << endl;
    }
    void SendMessage() override {
      cout << "HWNova SendMessage" << endl;
    }
};

enum phone_type {
  HWMATE = 0,
  HWNOVA = 1,
};

// 工厂
class HWFactory {
 public:
  IPhone* CreatePhone(int phone_type) {
    switch (phone_type) {
      case HWMATE:
        return new HWMate();
      case HWNOVA:
        return new HWNova();
      default:
        return nullptr;
    }
    return nullptr;
  }
};

int main(void) {
  HWFactory factory;
  int phone_type;
  cin >> phone_type;
  IPhone* phone = factory.CreatePhone(phone_type);
  if (phone != nullptr) {
    phone->Call();
    phone->TakePicture();
    phone->SendMessage();
  }
  delete phone;
  return 0;
}