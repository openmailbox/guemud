#ifndef GUEMUD_CONNECTION_HANDLER_H_
#define GUEMUD_CONNECTION_HANDLER_H_

#include <string>

#include "connection.h"

namespace guemud {
  class ConnectionHandler {
    public:
      ConnectionHandler(Connection& conn);
      virtual void Handle(std::string data) = 0;
      virtual void Enter() = 0;
      virtual void Leave() = 0;
    protected:
      guemud::Connection* connection_;
  };
}

#endif
