#ifndef GUEMUD_GAME_H_
#define GUEMUD_GAME_H_

#include "networking/connection.h"
#include "player.h"
#include "player_database.h"
#include "room_database.h"

namespace guemud {

class Game {
 public:
  static Game& GetInstance();

  Game();

  void Announce(std::string text);
  void ExecuteLoop();
  bool IsRunning();

 private:
  static Game instance_;

  bool is_running_;
};

}  // namespace guemud

#endif
