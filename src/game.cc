#include "game.h"

namespace guemud {
  Game Game::instance_;

  Game& Game::GetInstance() { return instance_;  }

  Game::Game() {
    is_running_ = true;
    instance_ = *this;

    Room* room = RoomDB.Create(); // temporary - create a starting room
    room->SetName("Origin Room");
    room->SetDescription("This is where it all begins.");
  }

  void Game::Announce(std::string text) {
    std::vector<Player*>::iterator itr = PlayerDB.Begin();

    while (itr != PlayerDB.End()) {
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
