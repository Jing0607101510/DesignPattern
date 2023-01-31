#include <iostream>
#include <vector>
using namespace std;

// Receiver
class Receiver {
  public:
    void Call() {
      cout << "Call" << endl;
    }
    void TakePicture() {
      cout << "TakePicture" << endl;
    }
};

// Command
class Command {
  public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

class CallCommand : public Command {
  public:
    CallCommand(Receiver* r) {
      receiver = r;
    }
    void execute() override {
      receiver->Call();
    }
  private:
    Receiver* receiver;
};

class TakePictureCommand : public Command {
  public:
    TakePictureCommand(Receiver* r) {
      receiver = r;
    }
    void execute() override {
      receiver->TakePicture();
    }
  private:
    Receiver* receiver;
};

// invoker
class PhoneInvoker {
  public:
    void AddCommandList(Command* cmd) {
      commands.push_back(cmd);
    }
    void DoCommands() {
      for (auto cmd : commands) {
        cmd->execute();
      }
      commands.clear();
    }
  private:
    vector<Command*> commands;
};


// client
int main(void) {
  Receiver* r = new Receiver();
  Command* call = new CallCommand(r);
  Command* take_pic = new TakePictureCommand(r);
  PhoneInvoker phone;
  phone.AddCommandList(call);
  phone.AddCommandList(take_pic);
  phone.DoCommands();
  delete take_pic;
  delete call;
  delete r;
  return 0;
}