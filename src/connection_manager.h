#ifndef GUEMUD_CONNECTION_MANAGER_H_
#define GUEMUD_CONNECTION_MANAGER_H_

#include <errno.h>
#include <sys/select.h>
#include <sys/socket.h>

#include <cstddef>
#include <iostream>
#include <set>

#include "connection_manager.h"

namespace guemud {
  class ConnectionManager {
    public:
      ConnectionManager();
      void Manage();
      void NewConnection(int socket);
    private:
      fd_set        socket_set_;
      fd_set        activity_set_;
      std::set<int> sockets_;
  };
}

#endif
