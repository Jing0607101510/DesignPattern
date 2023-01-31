#include <iostream>
using namespace std;

class SubSystem1 {
  public:
    void method() {
      cout << "Sys1" << endl;
    }
};

class SubSystem2 {
  public:
    void method() {
      cout << "sys2" << endl;
    }
};

class SubSystem3 {
  public:
    void method() {
      cout << "sys3" << endl;
    }
};

class Facade {
  private:
    SubSystem1 sys1;
    SubSystem2 sys2;
    SubSystem3 sys3;
  public:
    void Method() {
      sys1.method();
      sys2.method();
      sys3.method();
    }
};

int main(void) {
  Facade facade;
  facade.Method();
  return 0;
}