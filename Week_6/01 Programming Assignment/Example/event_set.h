#pragma once

#include <algorithm>
#include <string>
#include <set>
#include <vector>
using namespace std;

class EventSet {
public:
  void Add(const string& event);

  const vector<string>& GetAll() const;

  template <typename Predicate>
  int RemoveIf(Predicate predicate) {
    auto split_point = stable_partition(event_order_.begin(), event_order_.end(), predicate);
    int result = split_point - event_order_.begin();
    for (auto i = event_order_.begin(); i != split_point; ++i) {
      events_.erase(*i);
    }
    event_order_.erase(event_order_.begin(), split_point);

    return result;
  }

private:
  set<string> events_;
  vector<string> event_order_;
};

