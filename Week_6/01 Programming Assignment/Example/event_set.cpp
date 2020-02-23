#include "event_set.h"

void EventSet::Add(const string& event) {
  auto insert_result = events_.insert(event);
  if (insert_result.second) {
    event_order_.push_back(event);
  }
}

const vector<string>& EventSet::GetAll() const {
  return event_order_;
}
