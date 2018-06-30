#ifndef GUEMUD_GAME_H_
#define GUEMUD_GAME_H_

#include "action.h"
#include "database.h"
#include "networking/connection.h"
#include "player.h"

namespace guemud {

class Game {
 public:
  static Game& GetInstance();

  Game();

  void Announce(std::string text);
  void DoAction(Action action);
  void ExecuteLoop();
  bool IsRunning();

 private:
  static Game instance_;

  bool is_running_;

  void ShowRoom(Player& player);
};

}  // namespace guemud

#endif
