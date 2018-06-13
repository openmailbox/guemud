#ifndef GUEMUD_LISTENING_SOCKET_H_
#define GUEMUD_LISTENING_SOCKET_H_

#include <errno.h>
#include <string.h>

#include "socket.h"

namespace guemud {
  class ListeningSocket : Socket {
    public:
      void Listen(int port);
  };
}

#endif
