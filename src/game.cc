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

void guemud::Game::DoAction(Action action) {
  if (action.action_type == "look") {
    Player* player = PlayerDB.Load(action.entities[0].id);
    ShowRoom(*player);
  }
}

void Game::ExecuteLoop() {
  // perform actions
}

bool Game::IsRunning() { return is_running_; }

void guemud::Game::ShowRoom(Player& player) {
  Entity::Reference ref        = player.GetLocation();
  networking::Connection* conn = player.GetConnection();
  Room* room                   = RoomDB.Load(ref.id);

  std::vector<Entity::Reference>::iterator itr = room->BeginContents();

  conn->GetProtocol()->SendString(*conn, room->GetName() + "\n");
  conn->GetProtocol()->SendString(*conn, room->GetDescription() + "\n");
  conn->GetProtocol()->SendString(*conn, "Players here:\n");

  while (itr != room->EndContents()) {
    Player* player = PlayerDB.Load((*itr).id);
    conn->GetProtocol()->SendString(*conn, player->GetName() + "\n");
    itr++;
  }
}

void guemud::Game::Stop() {
  is_running_ = false;
}

}  // namespace guemud
