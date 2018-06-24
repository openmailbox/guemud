#ifndef GUEMUD_CHAT_H_
#define GUEMUD_CHAT_H_

#include "networking/connection_handler.h"

namespace guemud {
  class Chat : public networking::ConnectionHandler {
    public:
      Chat(networking::Connection* conn);
      void Enter();
      void Handle(std::string data);
    private:
      void ShowPrompt();
  };
}

#endif
