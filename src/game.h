#ifndef GUEMUD_GAME_H_
#define GUEMUD_GAME_H_

#include <chrono>
#include <queue>

#include "action.h"
#include "database.h"
#include "networking/connection.h"
#include "player.h"
#include "timed_action.h"

namespace guemud {

typedef std::priority_queue<TimedAction*, std::vector<TimedAction*>,
                            TimedAction::Compare>
    TimerQueue;

class Game {
 public:
  static Game& GetInstance();

  Game();

  void AddAction(Action action, unsigned int seconds_from_now = 0);
  void Announce(std::string text);
  void DoAction(Action& action);
  void ExecuteLoop();
  bool IsRunning();
  void Stop();

 private:
  static Game* instance_;

  bool is_running_;
  TimerQueue timer_registry_;

  void ShowRoom(Player& player);
};

}  // namespace guemud

#endif
