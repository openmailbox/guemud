#ifndef GUEMUD_NETWORKING_SOCKET_H_
#define GUEMUD_NETWORKING_SOCKET_H_

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#else
#include <netinet/in.h> // defines IPPROTO_TCP and sockaddr_in
#include <sys/socket.h>
#endif
#include <sys/types.h>

namespace guemud {
  namespace networking {
    class Socket {
      public:
        int GetSocket();
      protected:
        struct sockaddr_in local_info_;
        int socket_;
    };
  }
}

#endif
