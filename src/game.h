#ifndef GUEMUD_GAME_H_
#define GUEMUD_GAME_H_

#include <vector>

#include "networking/connection.h"
#include "player.h"
#include "room_database.h"

namespace guemud {
  class Game {
    public:
      static Game& GetInstance();

      Game();

      void                  Announce(std::string text);
      std::vector<Player*>* GetPlayers();
      void                  ExecuteLoop();
      Player*               NewPlayer(networking::Connection* conn, std::string name);
      bool                  IsRunning();
    private:
      static Game instance_;

      bool                 is_running_;
      std::vector<Player*> players_;
  };
}

#endif
