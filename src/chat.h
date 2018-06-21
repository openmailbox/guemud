#ifndef GUEMUD_CHAT_H_
#define GUEMUD_CHAT_H_

#include "connection_handler.h"

namespace guemud {
  class Chat : public ConnectionHandler {
    public:
      Chat(Connection& conn);
      void Enter();
      void Handle(std::string data);
    private:
      void ShowPrompt();
  };
}

#endif
