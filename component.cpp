#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Component {
  public:
    virtual void AddChild(Component* child) = 0;
    virtual void RemoveChild(int idx) = 0;
    virtual Component* GetChild(int idx) = 0;
    virtual void Operate() = 0;
    virtual ~Component() {}
  protected:
    string name;
};

class Leaf : public Component {
  public:
    Leaf(const string& name) { this->name = name; }
    void AddChild(Component* child) {}
    void RemoveChild(int idx) {}
    Component* GetChild(int idx) { return nullptr; }
    void Operate() {
      cout << "Leaf " << name << endl;
    }
};

class Composite : public Component {
  public:
    Composite(const string& name) { this->name = name; }
    void AddChild(Component* child) {
      children.push_back(child);
    }
    void RemoveChild(int idx) {
      if (idx < 0 || idx >= children.size()) {
        return;
      }
      swap(children[idx], children[children.size()-1]);
      children.pop_back();
    }
    Component* GetChild(int idx) {
      if (idx < 0 || idx >= children.size()) {
        return nullptr;
      }
      return children[idx];
    }
    void Operate() {
      cout << name << endl;
      for (auto child : children) {
        child->Operate();
      }
    }
  private:
    vector<Component*> children;
};

int main(void) {
  Component* root = new Composite("root");
  Component* node1 = new Composite("node1");
  Component* leaf1 = new Leaf("leaf1");
  Component* leaf2 = new Leaf("leaf2");
  Component* leaf3 = new Leaf("leaf3");
  root->AddChild(node1);
  root->AddChild(leaf1);
  node1->AddChild(leaf2);
  node1->AddChild(leaf3);
  root->Operate();

  delete root;
  delete leaf1;
  delete leaf2;
  delete leaf3;
  delete node1;
  return 0;
}