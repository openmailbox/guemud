#ifndef GUEMUD_CONNECTION_HANDLER_H_
#define GUEMUD_CONNECTION_HANDLER_H_

#include <string>

namespace guemud {
  class Connection; // forward declaration

  class ConnectionHandler {
    public:
      ConnectionHandler(Connection& conn);
      virtual void Enter() = 0;
    protected:
      guemud::Connection* connection_;
  };
}

#endif
