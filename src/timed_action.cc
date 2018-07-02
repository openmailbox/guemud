#include "timed_action.h"

namespace guemud {

bool TimedAction::Compare::operator()(const TimedAction* lhs, const TimedAction* rhs) {
  return lhs->execution_time < rhs->execution_time;
}

}
