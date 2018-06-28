#ifndef GUEMUD_LOGON_H_
#define GUEMUD_LOGON_H_

#include "chat.h"
#include "database.h"
#include "game.h"
#include "networking/connection_handler.h"
#include "room.h"

namespace guemud {
class Logon : public networking::ConnectionHandler {
 public:
  Logon(networking::Connection* conn);
  void Enter();
  void Handle(std::string data);
};
}  // namespace guemud

#endif
