#ifndef GUEMUD_CONNECTION_MANAGER_H_
#define GUEMUD_CONNECTION_MANAGER_H_

#include "connection_manager.h"

namespace guemud {
  class ConnectionManager {
    public:
      void NewConnection(int socket);
  };
}

#endif
