#include <unordered_map>
#include <iostream>
using namespace std;

class Expression {
  public:
    virtual int interpret(const unordered_map<char, int>& values) = 0;
    virtual ~Expression() {}
};

class TerminalExpression : public Expression {
  public:
    TerminalExpression(char key) : key(key) {}
    int interpret(const unordered_map<char, int>& values) {
      if (values.count(key)) {
        return values.at(key);
      } else {
        return 0;
      }
    }
  private:
    char key;
};

class NonTerminalExpression : public Expression {
  public:
    NonTerminalExpression(Expression* exp1, Expression* exp2) :
      exp1(exp1), exp2(exp2) {}
    virtual ~NonTerminalExpression() {}
  protected:
    Expression* exp1;
    Expression* exp2;
};

class AddExpression : public NonTerminalExpression {
  public:
    AddExpression(Expression* exp1, Expression* exp2) : NonTerminalExpression(exp1, exp2) {}
    int interpret(const unordered_map<char, int>& values) {
      return exp1->interpret(values) + exp2->interpret(values);
    }
};

class SubExpression : public NonTerminalExpression {
  public:
    SubExpression(Expression* exp1, Expression* exp2) : NonTerminalExpression(exp1, exp2) {}
    int interpret(const unordered_map<char, int>& values) {
      return exp1->interpret(values) - exp2->interpret(values);
    }
};

int main(void) {
  Expression* e1 = new TerminalExpression('a');
  Expression* e2 = new TerminalExpression('b');
  Expression* e3 = new TerminalExpression('c');
  Expression* e4 = new AddExpression(e1, e2);
  Expression* e5 = new SubExpression(e4, e3);

  unordered_map<char, int> values = {
    {'a', 10},
    {'b', 5},
    {'c', 20},
  };
  cout << "result: " << e5->interpret(values) << endl;

  delete e1;
  delete e2;
  delete e3;
  delete e4;
  delete e5;

  return 0;
}