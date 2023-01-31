#include <iostream>

using namespace std;

class Shape {
  public:
    virtual void Draw() = 0;
    virtual ~Shape() {}
};

class CircleShape : public Shape {
  public:
    void Draw() override {
      cout << "Draw Circle" << endl;
    }
};

class ShapeDecorator : public Shape {
  public:
    ShapeDecorator(Shape* shape) {
      this->shape = shape;
    }
    virtual void Draw() override {
      shape->Draw();
    }
    virtual ~ShapeDecorator() {}
  private:
    Shape* shape;
};

class ShapeBorderDecorator : ShapeDecorator {
  public:
    ShapeBorderDecorator(Shape* shape) : ShapeDecorator(shape) {}
    void Draw() {
      ShapeDecorator::Draw();
      cout << "Draw ShapeBorder" << endl;
    }
};

int main(void) {
  Shape* circle = new CircleShape();
  ShapeBorderDecorator decorator(circle);
  decorator.Draw();
  delete circle;
  return 0;
}