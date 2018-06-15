#ifndef GUEMUD_LISTENING_MANAGER_H_
#define GUEMUD_LISTENING_MANAGER_H_

#include "connection_manager.h"
#include "listening_socket.h"

namespace guemud {
  class ListeningManager {
    public:
      ListeningManager(int port, ConnectionManager manager);
      void Listen();
    private:
      ConnectionManager connection_manager_;
      int               port_;
      ListeningSocket   socket_;
  };
}

#endif
