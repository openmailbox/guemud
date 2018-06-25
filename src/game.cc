#include "game.h"

namespace guemud {
  Game Game::instance_;

  Game& Game::GetInstance() { return instance_;  }

  Game::Game() { 
    is_running_ = true; 
    instance_ = *this;
  }

  void guemud::Game::Announce(std::string text) {
    std::vector<Player>::iterator itr = players_.begin();

    while (itr != players_.end()) {
      networking::Connection* conn = (*itr).GetConnection();
      conn->GetProtocol()->SendString(*conn, text);
      itr++;
    }
  }

  void Game::ExecuteLoop() {
    // perform actions
  }

  Player Game::NewPlayer(networking::Connection* conn, std::string name) {
    Player new_player(conn, name);

    Announce(name + " has connected.\n");

    players_.push_back(new_player);

    return new_player;
  }

  bool Game::IsRunning() { return is_running_; }

}  // namespace guemud