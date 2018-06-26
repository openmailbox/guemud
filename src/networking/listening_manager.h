#ifndef GUEMUD_NETWORKING_LISTENING_MANAGER_H_
#define GUEMUD_NETWORKING_LISTENING_MANAGER_H_

#include "connection_manager.h"
#include "listening_socket.h"

#include "../error.h"

namespace guemud {
  namespace networking {
    class ListeningManager {
     public:
      ListeningManager(int port, ConnectionManager& manager);
      void Listen();

     private:
      ConnectionManager& connection_manager_;
      int port_;
      ListeningSocket socket_;
    };
  }  // namespace networking
}  // namespace guemud

#endif
