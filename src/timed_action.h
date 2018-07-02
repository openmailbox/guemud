#pragma once

#include <chrono>

#include "action.h"

namespace guemud {

struct TimedAction {
  struct Compare {
    bool operator()(const TimedAction* lhs, const TimedAction* rhs);
  };

  Action                                             action;
  std::chrono::time_point<std::chrono::steady_clock> execution_time;
};

}
