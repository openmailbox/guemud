#ifndef GUEMUD_NETWORKING_CONNECTION_MANAGER_H_
#define GUEMUD_NETWORKING_CONNECTION_MANAGER_H_


#include <errno.h>
#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/select.h>
#include <sys/socket.h>
#endif

#include <cstddef>
#include <iostream>
#include <set>

#include "connection.h"
#include "connection_manager.h"
#include "../logon.h"

namespace guemud {
  namespace networking {
    class ConnectionManager {
      public:
        ConnectionManager();
        void Manage();
        void NewConnection(int socket);
      private:
        fd_set                                     socket_set_;
        fd_set                                     activity_set_;
        std::set<Connection*, Connection::Compare> connections_;

        void Listen();
        void Send();
    };
  }
}

#endif
