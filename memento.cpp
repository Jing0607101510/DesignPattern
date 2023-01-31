#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Memento {
  public:
    Memento(const string& state) : state(state) {}
    string GetState() {
      return state;
    }
  private:
    string state;
};

class Originator {
  public:
    void SetState(const string& state) {
      this->state = state;
    }
    const string& GetState() {
      return this->state;
    }
    Memento* SaveStateToMemento() {
      return new Memento(this->state);
    }
    void LoadStateFromMemento(Memento* memento) {
      state = memento->GetState();
    }
  private:
    string state;
};

class CareTaker {
  private:
    vector<Memento*> mementos;
  public:
    void Add(Memento* memento) {
      mementos.push_back(memento);
    }
    Memento* Get(int idx) {
      if (idx < 0 || idx >= mementos.size()) {
        return nullptr;
      } else {
        return mementos[idx];
      }
    }
};

int main(void) {
  Originator o;
  o.SetState("State1");
  o.SetState("State2");
  Memento* m = o.SaveStateToMemento();
  CareTaker t;
  t.Add(m);
  o.SetState("State3");
  cout << "Before Load:" << o.GetState() << endl;
  o.LoadStateFromMemento(t.Get(0));
  cout << "After Load:" << o.GetState() << endl;
  return 0;
}