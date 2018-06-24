#include "connection_handler.h"
#include "connection.h"

namespace guemud {
  namespace networking {
    ConnectionHandler::ConnectionHandler(Connection* conn) : connection_(conn) {};
  }
}
