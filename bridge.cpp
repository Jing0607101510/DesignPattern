#include <iostream>
#include <string>
#include <vector>
using namespace std;

class App {
  public:
    virtual void SetPlatformName(const string& name) = 0;
    virtual void ShowLogo() = 0;
    virtual ~App() {}
  protected:
    string name;
};

class WxApp : public App {
  public:
    void SetPlatformName(const string& name) override {
      this->name = name;
    }
    void ShowLogo() override {
      cout << name << " " << "Wx" << endl << endl;
    }
};

class MaiMainApp : public App {
  public:
    void SetPlatformName(const string& name) override {
      this->name = name;
    }
    void ShowLogo() override {
      cout << name << " " << "MaiMai" << endl << endl;
    }
};

class Phone {
  public:
    virtual void InstallApp(App* app) = 0;
    virtual void EnterApp(App* app) = 0;
    virtual ~Phone() {}
  protected:
    vector<App*> apps;
};

class MetaPhone : public Phone {
  public:
    void InstallApp(App* app) override {
      app->SetPlatformName("Meta");
      apps.push_back(app);
    }
    void EnterApp(App* app) override {
      if (app) {
        app->ShowLogo();
      }
    }
};

class NovaPhone : public Phone {
  public:
    void InstallApp(App* app) override {
      app->SetPlatformName("Nova");
      apps.push_back(app);
    }
    void EnterApp(App* app) override {
      if (app) {
        app->ShowLogo();
      }
    }
};

int main(void) {
  App* wx_app = new WxApp();
  App* mai_app = new MaiMainApp();
  Phone* meta_phone = new MetaPhone();
  Phone* nova_phone = new NovaPhone();
  meta_phone->InstallApp(wx_app);
  meta_phone->EnterApp(wx_app);
  meta_phone->InstallApp(mai_app);
  meta_phone->EnterApp(mai_app);
  nova_phone->InstallApp(wx_app);
  nova_phone->EnterApp(wx_app);
  nova_phone->InstallApp(mai_app);
  nova_phone->EnterApp(mai_app);

  delete nova_phone;
  delete meta_phone;
  delete wx_app;
  delete mai_app;
  return 0;
}