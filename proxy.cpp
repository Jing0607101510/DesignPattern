#include <iostream>
using namespace std;

class Image {
  public:
    virtual void display() = 0;
    virtual ~Image() {}
};

class RealImage : public Image{
  public:
    RealImage(const string& name) : name(name) {}
    void display() {
      cout << "Display File " << name << endl;
      LoadFromDisk();
    }
    void LoadFromDisk() {
      cout << "Load File " << name << " From Disk" << endl;
    }
  private:
    string name;
};

class ProxyImage : public Image{
  public:
    ProxyImage(const string& name) : name(name) {}

    void display() {
      if (image == nullptr) {
        image = new RealImage(name);
      }
      image->display();
    }
  private:
    RealImage* image;
    string name;
};

int main(void) {
  ProxyImage* image = new ProxyImage("C++");
  image->display();
  return 0;
}