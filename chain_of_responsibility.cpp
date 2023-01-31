#include <iostream>
using namespace std;

class ILogger {
  public:
    const static int INFO = 1;
    const static int DEBUG = 2;
    const static int ERROR = 3;
    
    void SetNextLogger(ILogger* logger) {
      next_logger = logger;
    }

    void LogMessage(int msg_level, const string& msg) {
      if (msg_level >= level) {
        Process(msg);
      }
      if (next_logger) {
        next_logger->LogMessage(msg_level, msg);
      }
    }
    virtual void Process(const string& msg) = 0;
    virtual ~ILogger() {}
  protected:
    int level;
    ILogger* next_logger;
};

class ErrorLogger : public ILogger {
  public:
    ErrorLogger(int level, ILogger* logger = nullptr) {
      this->level = level;
      this->next_logger = logger;
    }
    void Process(const string& msg) {
      cout << "Error: " << msg << endl;
    }
};

class FileLogger : public ILogger {
  public:
    FileLogger(int level, ILogger* logger = nullptr) {
      this->level = level;
      this->next_logger = logger;
    }
    void Process(const string& msg) {
      cout << "File: " << msg << endl;
    }
};

class ConsoleLogger : public ILogger {
  public:
    ConsoleLogger(int level, ILogger* logger = nullptr) {
      this->level = level;
      this->next_logger = logger;
    }
    void Process(const string& msg) {
      cout << "Console: " << msg << endl;
    }
};

int main(void) {
  // 链成责任链
  ILogger* error = new ErrorLogger(3);
  ILogger* file = new FileLogger(2, error);
  ILogger* console = new ConsoleLogger(1, file);

  console->LogMessage(1, "Hello1");
  cout << endl;

  console->LogMessage(2, "Hello2");
  cout << endl;

  console->LogMessage(3, "Hello3");

  return 0;
}