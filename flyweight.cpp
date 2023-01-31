#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Book {
  public:
    virtual void Borrow() = 0;
    virtual ~Book() {}
};

class ConcreteBook : public Book {
  private:
    string name;
  public:
    ConcreteBook(const string& name) : name(name) {}
    void Borrow() override {
      cout << "Borrow " << name << endl;
    }
};

class BookFactory {
  public:
    static BookFactory* GetInstance() {
      return factory;
    }

    Book* GetBook(const string& name) {
      if (name2book.count(name)) {
        return name2book[name];
      } else {
        name2book[name] = new ConcreteBook(name);
        return name2book[name];
      }
    }

    int GetSize() {
      return name2book.size();
    }
  private:
    BookFactory() {}
    ~BookFactory() {
      for (auto book : name2book) {
        delete book.second;
      }
    }
    static BookFactory* factory;
    unordered_map<string, Book*> name2book;
};

BookFactory* BookFactory::factory = new BookFactory();

int main(void) {
  vector<Book*> books;
  BookFactory* factory = BookFactory::GetInstance();
  books.push_back(factory->GetBook("C++"));
  books.push_back(factory->GetBook("Java"));
  books.push_back(factory->GetBook("Python"));
  books.push_back(factory->GetBook("Java"));
  books.push_back(factory->GetBook("Python"));
  for (auto book : books) {
    book->Borrow();
  }

  cout << "Borrow: " << books.size() << endl;
  cout << "实际Borrow: " << factory->GetSize() << endl;

  return 0;
}