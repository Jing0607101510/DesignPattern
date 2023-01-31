#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Observer {
  public:
    virtual void Update(const std::string& msg) = 0;
    virtual ~Observer() {}
};

class Subject {
  public:
    virtual void Notify(const std::string& msg) = 0;
    virtual int Register(Observer* observer) = 0;
    virtual int UnRegister(Observer* observer) = 0;
    virtual ~Subject() {}
};

class Audience : public Observer {
  public:
    void Update(const std::string& msg) override {
      cout << "audience observer: " << msg << endl;
    }
};

class Assistant : public Observer {
  public:
    void Update(const string& msg) override {
      cout << "assistant observer: " << msg << endl;
    }
};

class Anchor : public Subject {
  public:
    void Notify(const string& msg) override {
      for (auto* observer : observers) {
        observer->Update(msg);
      }
    }
    int Register(Observer* observer) override {
      if (observer) {
        observers.push_back(observer);
      }
      return 0;
    }
    int UnRegister(Observer* observer) override {
      for (auto it = observers.begin(); it != observers.end(); it++) {
        if (*it == observer) {
          observers.erase(it);
          break;
        }
      }
      return 0;
    }
  private:
    vector<Observer*> observers;
};

int main(void) {
  Subject* anchor = new Anchor();
  Observer* assistant = new Assistant();
  Observer* audience = new Audience();
  anchor->Notify("Hello World!");
  cout << endl;

  anchor->Register(assistant);
  anchor->Register(audience);
  anchor->Notify("You are well!");

  anchor->UnRegister(assistant);
  anchor->Notify("Thank you!");

  delete anchor;
  delete assistant;
  delete audience;
  return 0;
}