#include <iostream>
using namespace std;

class Game {
  public:
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void End() = 0;
    void Process() {
      Init();
      Start();
      End();
    }
    virtual ~Game() {}
};

class FootBall : public Game {
  public:
    void Init() {
      cout << "Init FootBall Game" << endl;
    }
    void Start() {
      cout << "Start FootBall Game" << endl;
    }
    void End() {
      cout << "End FootBall Game" << endl;
    }
};

class Tennis : public Game {
  public:
    void Init() {
      cout << "Init Tennis Game" << endl;
    }
    void Start() {
      cout << "Start Tennis Game" << endl;
    }
    void End() {
      cout << "End Tennis Game" << endl;
    }
};

int main(void) {
  Game* football = new FootBall();
  Game* tennis = new Tennis();
  football->Process();
  tennis->Process();
  delete football;
  delete tennis;
  return 0;
}