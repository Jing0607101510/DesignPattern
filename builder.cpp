#include <iostream>
#include <string>
using namespace std;

class Phone {
  public:
    virtual void SetName(const string& name) = 0;
    virtual void SetCpu(const string& cpu) = 0;
    virtual void SetSceen(const string& sceen) = 0;
    virtual string GetName() const  = 0;
    virtual string GetCpu() const = 0;
    virtual string GetSceen() const = 0;
    virtual ~Phone() {}
    void Print() {
      cout << "Name: " << name << endl
           << "Cpu: " << cpu << endl
           << "Sceen: " << sceen << endl;
    }
  protected:
    string name;
    string cpu;
    string sceen;
};

class MetaPhone : public Phone {
  public:
    void SetName(const string& name) override {
      this->name = name;
    }
    string GetName() const override {
      return name;
    }
    void SetCpu(const string& cpu) override {
      this->cpu = cpu;
    }
    string GetCpu() const override {
      return cpu;
    }
    void SetSceen(const string& sceen) override {
      this->sceen = sceen;
    }
    string GetSceen() const override {
      return sceen;
    }
};

class Builder {
  public:
    virtual void BuildName() = 0;
    virtual void BuildCpu() = 0;
    virtual void BuildSceen() = 0;
    virtual ~Builder() {}
    Phone* GetPhone() {
      return phone;
    }
  
  protected:
    Phone* phone;
};

class MetaPhoneBuilder : public Builder {
  public:
    MetaPhoneBuilder() {
      phone = new MetaPhone();
    }
    ~MetaPhoneBuilder() {
      delete phone;
    }
    void BuildName() override {
      phone->SetName("Meta");
    }
    void BuildCpu() override {
      phone->SetCpu("Meta Cpu");
    }
    void BuildSceen() override {
      phone->SetSceen("Meta Sceen");
    }
};

class Director {
  public:
    void BuildPhone(Builder* builder) {
      if (builder) {
        builder->BuildName();
        builder->BuildCpu();
        builder->BuildSceen();
      }
    }
};

int main(void) {
  Director* director = new Director();
  Builder* meta_builder = new MetaPhoneBuilder();
  director->BuildPhone(meta_builder);
  Phone* meta_phone = meta_builder->GetPhone();
  meta_phone->Print();
  delete director;
  delete meta_builder;
  return 0;
}