#include "game.h"

namespace guemud {

Game* Game::instance_;

Game& Game::GetInstance() { return *instance_; }

Game::Game() {
  is_running_ = true;
  instance_ = this;
}

void Game::AddAction(Action action, unsigned int seconds_from_now) {
  TimedAction* timed_action = new TimedAction();

  std::chrono::duration<int> offset(seconds_from_now);
  std::chrono::time_point<std::chrono::steady_clock> time =
      std::chrono::steady_clock::now() + offset;

  timed_action->action = action;
  timed_action->execution_time = time;

  timer_registry_.push(timed_action);
}

void Game::Announce(std::string text) {
  std::vector<Player*>::iterator itr = database::PlayerDB.Begin();

  while (itr != database::PlayerDB.End()) {
    networking::Connection* conn = (*itr)->GetConnection();
    conn->GetProtocol()->SendString(*conn, text);
    itr++;
  }
}

void guemud::Game::DoAction(Action& action) {
  if (action.action_type == "look") {
    Player* player = database::PlayerDB.Load(action.entities[0].id);
    ShowRoom(*player);
  } else if (action.action_type == "chat") {
    Player* player = database::PlayerDB.Load(action.entities[0].id);
    Announce("<chat> " + player->GetName() + " says, \"" + action.data + "\"\n");
  } else if (action.action_type == "quit") {
    Player* player = database::PlayerDB.Load(action.entities[0].id);
    Room* room = database::RoomDB.Load(player->GetLocation().id);
    std::string name = player->GetName();

    room->Remove(action.entities[0]);
    player->GetConnection()->Close();
    database::PlayerDB.Unload(player->GetId());

    Announce("<chat> " + name + " has disconnected.\n");
  }
}

void Game::ExecuteLoop() {
  if (timer_registry_.size() == 0) return;

  std::chrono::steady_clock::time_point current_time =
      std::chrono::steady_clock::now();

  while (timer_registry_.size() > 0 &&
         timer_registry_.top()->execution_time < current_time) {
    TimedAction* next_action = timer_registry_.top();

    timer_registry_.pop();

    DoAction(next_action->action);

    delete next_action;
  }
}

bool Game::IsRunning() { return is_running_; }

void guemud::Game::ShowRoom(Player& player) {
  Entity::Reference ref = player.GetLocation();
  networking::Connection* conn = player.GetConnection();
  Room* room = database::RoomDB.Load(ref.id);

  std::vector<Entity::Reference>::iterator itr = room->BeginContents();

  conn->GetProtocol()->SendString(*conn, room->GetName() + "\n");
  conn->GetProtocol()->SendString(*conn, room->GetDescription() + "\n");
  conn->GetProtocol()->SendString(*conn, "Players here:\n");

  while (itr != room->EndContents()) {
    Player* player = database::PlayerDB.Load((*itr).id);
    conn->GetProtocol()->SendString(*conn, player->GetName() + "\n");
    itr++;
  }
}

void guemud::Game::Stop() { is_running_ = false; }

}  // namespace guemud
