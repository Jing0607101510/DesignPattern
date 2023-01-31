#include <vector>
#include <iostream>

using namespace std;

class Iterator {
  public:
    virtual bool HasNext() = 0;
    virtual int Next() = 0;
    virtual ~Iterator() {}
};

class Container {
  public:
    virtual ~Container() {}
};

class IntContainer : public Container  {
  friend class IntIterator;
  public:
    IntContainer() {
      for (int i = 0; i < 5; i++) {
        nums.push_back(i);
      }
    }
  private:
    vector<int> nums;
};


class IntIterator : public Iterator {
  private:
    int idx;
    IntContainer* container;
  public:
    IntIterator(IntContainer* container) : idx(0), container(container) {}
    IntIterator() : idx(0) {}
    bool HasNext() {
      if (idx >= container->nums.size()) {
        return false;
      }
      return true;
    }
    int Next() {
      if (HasNext()) {
        return container->nums[idx++];
      } else {
        return -1;
      }
    }
};

int main(void) {
  IntContainer* c = new IntContainer();
  IntIterator* it = new IntIterator(c);
  while (it->HasNext()) {
    cout << it->Next() << endl;
  }
  delete it;
  delete c;
  return 0;
}