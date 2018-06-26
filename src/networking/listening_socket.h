#ifndef GUEMUD_NETWORKING_LISTENING_SOCKET_H_
#define GUEMUD_NETWORKING_LISTENING_SOCKET_H_

#include <errno.h>
#include <string.h>

#include "../error.h"
#include "socket.h"

namespace guemud {
  namespace networking {
    class ListeningSocket : public Socket {
      public:
        void Listen(int port);

      private:
        void CheckErrors(int result);
    };
  }
}

#endif
