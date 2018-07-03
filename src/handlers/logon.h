#pragma once

#include "../database.h"
#include "../game.h"
#include "../networking/connection_handler.h"
#include "../room.h"
#include "game_handler.h"

namespace guemud {
namespace handlers {

class Logon : public networking::ConnectionHandler {
 public:
  Logon(networking::Connection* conn);
  void Enter();
  void Handle(std::string data);
};

}  // namespace handlers
}  // namespace guemud
