#ifndef GUEMUD_SOCKET_H_
#define GUEMUD_SOCKET_H_

#include <netinet/in.h> // defines IPPROTO_TCP and sockaddr_in
#include <sys/types.h>
#include <sys/socket.h>

namespace guemud {
  class Socket {
    protected:
      struct sockaddr_in local_info_;
      int socket_;
  };
}

#endif
