#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Visitor;

class ComputerPart {
  public:
    virtual void accept(Visitor* visitor) = 0;
    virtual ~ComputerPart() {}
};

class ComputerPartMouse;
class ComputerPartSceen;
class ComputerPartKeyBoard;
class Computer;

class Visitor {
  public:
    virtual void Visit(ComputerPartMouse* part) = 0;
    virtual void Visit(ComputerPartKeyBoard* part) = 0;
    virtual void Visit(Computer* part) = 0;
    virtual void Visit(ComputerPartSceen* part) = 0;
    virtual ~Visitor() {}
};

class ComputerPartVisitor : public Visitor {
  public:
    void Visit(ComputerPartMouse* part) {
      cout << "Visit Mouse" << endl;
    }
    void Visit(ComputerPartSceen* part) {
      cout << "Visit Sceen" << endl;
    }
    void Visit(Computer* part) {
      cout << "Visit Computer" << endl;
    }
    void Visit(ComputerPartKeyBoard* part) {
      cout << "Visit KeyBoard" << endl;
    }
};

class ComputerPartMouse : public ComputerPart {
  public:
    void accept(Visitor* visitor) override {
      visitor->Visit(this);
    };
};

class ComputerPartKeyBoard : public ComputerPart {
  public:
    void accept(Visitor* visitor) override {
      visitor->Visit(this);
    };
};

class ComputerPartSceen : public ComputerPart {
  public:
    void accept(Visitor* visitor) override {
      visitor->Visit(this);
    };
};

class Computer : public ComputerPart {
  public:
    Computer() {
      parts.push_back(new ComputerPartMouse());
      parts.push_back(new  ComputerPartSceen());
      parts.push_back(new ComputerPartSceen());
    }
    ~Computer() {
      for (auto part : parts) {
        delete part;
      }
    }
    void accept(Visitor* visitor) override {
      visitor->Visit(this);
      for (auto part : parts) {
        part->accept(visitor);
      }
    };
  private:
    vector<ComputerPart*> parts;
};

int main(void) {
  Visitor* visitor = new ComputerPartVisitor();
  ComputerPart* computer = new Computer();
  computer->accept(visitor);
  delete visitor;
  return 0;
}