#include <iostream>
#include <vector>

using namespace std;

class Person {
  public:
    Person(int idx, bool is_male, bool is_single) : is_male(is_male), is_single(is_single), idx(idx) {}
    bool IsMale() const {
      return is_male;
    }
    bool IsSingle() const {
      return is_single;
    }
    int GetIdx() const {
      return idx;
    }
  private:
    bool is_male;
    bool is_single;
    int idx;
};

class Filter {
  public:
    virtual vector<Person> MeetCriteria(const vector<Person>& persons) = 0;
    virtual ~Filter() {}
};

class FemaleFilter : public Filter {
  public:
    vector<Person> MeetCriteria(const vector<Person>& persons) {
      vector<Person> ans;
      for (auto& person : persons) {
        if (!person.IsMale()) {
          ans.push_back(person);
        }
      }
      return ans;
    }
};

class SingleFilter : public Filter {
  public:
    vector<Person> MeetCriteria(const vector<Person>& persons) {
      vector<Person> ans;
      for (auto& person : persons) {
        if (person.IsSingle()) {
          ans.push_back(person);
        }
      }
      return ans;
    }
};

class AndFilter : public Filter {
  public:
    AndFilter(Filter* filter1, Filter* filter2) : f1(filter1), f2(filter2) { }
    vector<Person> MeetCriteria(const vector<Person>& persons) {
      vector<Person> ans = f1->MeetCriteria(persons);
      ans = f2->MeetCriteria(ans);
      return ans;
    }
  private:
    Filter* f1;
    Filter* f2;
};

class OrFilter : public Filter {
  public:
    OrFilter(Filter* f1, Filter* f2) {
      this->f1 = f1;
      this->f2 = f2;
    }
    vector<Person> MeetCriteria(const vector<Person>& persons) {
      vector<Person> ans1 = f1->MeetCriteria(persons);
      vector<Person> ans2 = f2->MeetCriteria(persons);
      for (auto person : ans2) {
        bool found = false;
        for (auto p1 : ans1) {
          if (person.GetIdx() == p1.GetIdx()) {
            found = true;
            break;
          }
        }
        if (!found) {
          ans1.push_back(person);
        }
      }
      return ans1;
    }
  private:
    Filter* f1;
    Filter* f2;
};

void PrintPersons(const vector<Person>& persons) {
  for (auto person : persons) {
    cout << person.GetIdx() << " "; 
  }
  cout << endl;
}

int main(void) {
  vector<Person> persons1 {Person(0, false, false), Person(1, false, true), Person(2, true, false), Person(3, true, true)};
  vector<Person> Persons2 {Person(4, false, false), Person(5, false, true), Person(6, true, false), Person(7, true, true)};
  FemaleFilter f1;
  SingleFilter f2;
  AndFilter f3(&f1, &f2);
  OrFilter f4(&f1, &f2);
  vector<Person> ans = f1.MeetCriteria(persons1);
  PrintPersons(ans);

  ans = f2.MeetCriteria(persons1);
  PrintPersons(ans);

  ans = f3.MeetCriteria(persons1);
  PrintPersons(ans);

  ans = f4.MeetCriteria(persons1);
  PrintPersons(ans);

  return 0;
}