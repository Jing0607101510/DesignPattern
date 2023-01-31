#include <string>
#include <iostream>
using namespace std;

class Hero {
  private:
    int hp;
    string name;
  public:
    Hero(const string& name, int init_hp) {
      hp = init_hp;
      this->name = name;
    }
    void BeAttacked(int att) {
      if (hp > att) {
        hp -= att;
      } else {
        hp = 0;
      }
    }
    int GetHp() {
      return hp;
    }
    void SetHp(int hp) {
      this->hp = hp;
    }
    string GetName() {
      return name;
    }
};

class HeroView {
  public:
    void Show(const string& name, int hp) {
      cout << "Hero: " << name << " Hp: " << hp << endl;
    }
};

class HeroController {
  private:
    Hero* hero;
    HeroView* view;
  public:
    HeroController(const string& name) {
      hero = new Hero(name, 10);
      view = new HeroView();
    }
    void Show() {
      view->Show(hero->GetName(), hero->GetHp());
    }
    void BeAttacked(int att) {
      hero->BeAttacked(att);
    }
    ~HeroController() {
      delete hero;
      delete view;
    }
};

int main(void) {
  HeroController* controller = new HeroController("Joe");
  controller->Show();
  controller->BeAttacked(5);
  controller->Show();
  controller->BeAttacked(10);
  controller->Show();
  delete controller;
  return 0;
}