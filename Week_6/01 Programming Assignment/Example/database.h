#pragma once

#include "date.h"
#include "event_set.h"

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Entry {
  Date date;
  string event;
};

ostream& operator << (ostream& os, const Entry& e);
bool operator == (const Entry& lhs, const Entry& rhs);

class Database {
public:
  void Add(const Date& date, const string& event);

  template <typename Predicate>
  int RemoveIf(Predicate predicate) {
    int result = 0;
    for (auto& kv : data_) {
      const Date& date = kv.first;
      result += kv.second.RemoveIf([=](const string& event) {
        return predicate(date, event);
      });
    }
    for (auto it = data_.begin(); it != data_.end(); ) {
      if (it->second.GetAll().empty()) {
        data_.erase(it++);
      } else {
        ++it;
      }
    }
    return result;
  }

  template <typename Predicate>
  vector<Entry> FindIf(Predicate predicate) const {
    vector<Entry> result;
    for (auto& kv : data_) {
      for (const auto& event : kv.second.GetAll()) {
        if (predicate(kv.first, event)) {
          result.push_back(Entry{kv.first, event});
        }
      }
    }
    return result;
  }

  void Print(ostream& os) const;

  // throws invalid_argument if there is no last event for the given date
  Entry Last(const Date& date) const;

private:
  map<Date, EventSet> data_;
};

// Tests
void TestDatabaseAddAndPrint();
void TestDatabaseFind();
void TestDatabaseRemove();
void TestDatabaseLast();
