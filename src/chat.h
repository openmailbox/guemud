#ifndef GUEMUD_CHAT_H_
#define GUEMUD_CHAT_H_

#include "commands/who_command.h"
#include "game.h"
#include "networking/connection_handler.h"

namespace guemud {
  class Chat : public networking::ConnectionHandler {
   public:
     Chat(networking::Connection* conn, Player player);

     void Enter();
     void Handle(std::string data);

   private:
     Player player_;

     void ShowPrompt();
  };
}

#endif
