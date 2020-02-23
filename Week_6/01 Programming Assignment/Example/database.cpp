#include "database.h"
#include <algorithm>
#include <stdexcept>
#include <tuple>
using namespace std;

void Database::Add(const Date& date, const string& event) {
  data_[date].Add(event);
}

void Database::Print(ostream& os) const {
  for (const auto& kv : data_) {
    for (const auto& event : kv.second.GetAll()) {
      os << kv.first << ' ' << event << endl;
    }
  }
}

Entry Database::Last(const Date& date) const {
  auto it = data_.upper_bound(date);
  if (it == data_.begin()) {
    throw invalid_argument("");
  }
  --it;
  return {it->first, it->second.GetAll().back()};
}

ostream& operator << (ostream& os, const Entry& e) {
  return os << e.date << " " << e.event;
}

bool operator == (const Entry& lhs, const Entry& rhs) {
  return tie(lhs.date, lhs.event) == tie(rhs.date, rhs.event);
}
