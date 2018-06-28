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
    std::vector<Player*> online_players = PlayerDB.GetConnected();
    std::vector<Player*>::iterator itr  = online_players.begin();

    while (itr != online_players.end()) {
      networking::Connection* conn = (*itr)->GetConnection();
      conn->GetProtocol()->SendString(*conn, text);
      itr++;
    }
  }

  void Game::ExecuteLoop() {
    // perform actions
  }

  bool Game::IsRunning() { return is_running_; }

}  // namespace guemud
