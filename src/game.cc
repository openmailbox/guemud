#include "game.h"

namespace guemud {
  Game Game::instance_;

  Game& Game::GetInstance() { return instance_;  }

  Game::Game() {
    is_running_ = true;
    instance_ = *this;

    RoomDB.Create(); // temporary - create a starting room
  }

  void Game::Announce(std::string text) {
    std::vector<Entity*>::iterator itr = PlayerDB.Begin();

    while (itr != PlayerDB.End()) {
      networking::Connection* conn = ((Player*)(*itr))->GetConnection();
      conn->GetProtocol()->SendString(*conn, text);
      itr++;
    }
  }

  void Game::ExecuteLoop() {
    // perform actions
  }

  bool Game::IsRunning() { return is_running_; }

}  // namespace guemud
