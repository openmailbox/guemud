#pragma once

#include "../commands/chat_command.h"
#include "../commands/look_command.h"
#include "../commands/quit_command.h"
#include "../commands/who_command.h"
#include "../game.h"
#include "../networking/connection_handler.h"

namespace guemud {
namespace handlers {

class GameHandler : public networking::ConnectionHandler {
 public:
  GameHandler(networking::Connection* conn, Player* player);

  void Enter();
  void Handle(std::string data);

 private:
  Player* player_;

  void ShowPrompt();
};

}  // namespace guemud
}
