#include <iostream>
using namespace std;

class People;

class State {
  public:
    virtual void Handle(People* context) = 0;
    virtual ~State() {}
};

class People {
  private:
    State* state = nullptr;
    int age = 0;

  public:
    People(State* state) {
      this->state = state;
      this->age = 0;
    }
    int GetAge() const {
      return age;
    }
    void Request(int addition) {
      age += addition;
      if (state) {
        state->Handle(this);
      }
    }
    void ChangeState(State* new_state) {
      if (state) {
        delete state;
      }
      if (new_state) {
        cout << "Change State to " << typeid(*new_state).name() << endl;
      }
      state = new_state;
    }
    ~People() {
      delete state;
    }
};

class SleepState;

class WorkState : public State {
  public:
    void Handle(People* context) override {
      cout << "Working" << endl;
    }
};

class SleepState : public State {
  public:
    void Handle(People* context) override {
      cout << "Sleeping" << endl;
      if (context) {
        if (context->GetAge() >= 1) {
          context->ChangeState(new WorkState());
        }
      }
    }
};

int main(void) {
  People* people = new People(new SleepState());
  people->Request(100);
  delete people;
  return 0;
}