#ifndef GUEMUD_LOGON_H_
#define GUEMUD_LOGON_H_

#include "chat.h"
#include "connection_handler.h"

namespace guemud {
  class Logon : public ConnectionHandler {
    public:
      Logon(Connection& conn);
      void Enter();
      void Handle(std::string data);
  };
}

#endif
