#include <iostream>
using namespace std;

class USBInterface {
  public:
    virtual void ConnectV1() {
      cout << "Usb connect" << endl;
    }
    virtual ~USBInterface() {}
};

class TypeCInterface {
  public:
    virtual void ConnectV2() {
      cout << "TypeC connect" << endl;
    }
    virtual ~TypeCInterface() {}
};

class Adapter : public USBInterface {
  public:
    Adapter() {
      interface = new TypeCInterface();
    }
    ~Adapter() {
      delete interface;
    }
    void ConnectV1() override {
      interface->ConnectV2();
    }
  private:
    TypeCInterface* interface;
};

int main(void) {
  Adapter adapter;
  adapter.ConnectV1();
  return 0;
}