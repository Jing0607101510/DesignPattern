#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

class Mediator;
class User {
  public:
    User(int my_key, Mediator* mediator) : my_key(my_key), mediator(mediator) {}
    virtual void Send(int key, const string& msg) = 0;
    virtual void Receive(const string& msg) = 0;
    virtual ~User() {}
  protected:
    int my_key;
    Mediator* mediator;
};

class Mediator {
  public:
    virtual void Register(int key, User* user) = 0;
    virtual void Relay(int key, const string& msg) = 0;
    virtual ~Mediator() {}
};

class ConcreteMediator : public Mediator {
  public:
    void Register(int key, User* user) {
      if (key_to_user.count(key) == 0) {
        key_to_user[key] = user;
      }
    }
    void Relay(int key, const string& msg) {
      if (key_to_user.count(key)) {
        key_to_user[key]->Receive(msg);
      }
    }
  private:
    unordered_map<int, User*> key_to_user;
};

class CommUser : public User {
  public:
    CommUser(int key, Mediator* mediator) : User(key, mediator) {}
    void Send(int key, const string& msg) {
      cout << "CommUser " << my_key << " Send Msg: " << msg << " to User " << key << endl;
      this->mediator->Relay(key, msg);
    }
    void Receive(const string& msg) {
      cout << "CommUser " << my_key << " Receive Msg: " << msg << endl;
    }
};

class GlodUser : public User {
  public:
    GlodUser(int key, Mediator* mediator) : User(key, mediator) {}
    void Send(int key, const string& msg) {
        cout << "GlodUser " << my_key << " Send Msg: " << msg << " to User " << key << endl;
        this->mediator->Relay(key, msg);
    }
    void Receive(const string& msg) {
      cout << "GlodUser " << my_key << " Receive Msg: " << msg << endl;
    }
};

int main(void) {
  int id = 0;
  ConcreteMediator mediator;
  User* user1 = new CommUser(id, &mediator);
  mediator.Register(id++, user1);
  User* user2 = new GlodUser(id, &mediator);
  mediator.Register(id++, user2);

  user1->Send(1, "Hello World!");
  user2->Send(0, "Fine. Thank you!");

  delete user1;
  delete user2;
  return 0;
}