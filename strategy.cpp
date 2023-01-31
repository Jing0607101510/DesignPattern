#include <iostream>
using namespace std;

class Comsumer {
  public:
    void SetDiscountRate(float rate) {
      this->rate = rate;
    }
    float GetDiscountRate() const {
      return rate;
    }
    virtual float GetPrice(float init_price) = 0;
    virtual ~Comsumer() {}
  protected:
    float rate;
};

class CommComsumer : public Comsumer {
  public:
    CommComsumer() { rate = 1.0; }
    float GetPrice(float init_price) override {
      return rate * init_price;
    }
};

class GlodComsumer : public Comsumer {
  public:
    GlodComsumer() { rate = 0.9; }
    float GetPrice(float init_price) override {
      return 0 > rate * init_price - 1 ? 0 : rate * init_price - 1;
    }
};

class Shop {
  public:
    Shop(Comsumer* comsumer) {
      this->consumer = comsumer;
    }
    void SetComsumer(Comsumer* c) {
      consumer = c;
    }
    float GetRealPrice(float price) {
      return consumer->GetPrice(price);
    }
  private:
    Comsumer* consumer;
};

int main(void) {
  Comsumer* c1 = new CommComsumer();
  Comsumer* c2 = new GlodComsumer();
  Shop shop(c1);
  cout << "CommComsumer Real Price: " << shop.GetRealPrice(1000) << endl;
  shop.SetComsumer(c2);
  cout << "GlodComsumer Real Price: " << shop.GetRealPrice(1000) << endl;
  delete c1;
  delete c2;
  return 0;
}