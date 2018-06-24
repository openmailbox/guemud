#include "listening_socket.h"

namespace guemud {
  namespace networking {
    void ListeningSocket::Listen( int port ) {
      #ifdef WIN32
        unsigned long mode = 1;
        socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (socket_ == INVALID_SOCKET) throw WSAGetLastError();

        ioctlsocket(socket_, FIONBIO, &mode);
      #else
        socket_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
        if (socket_ == -1) throw errno;
      #endif

      int reuse = 1;
      int err = setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, (char*)(&reuse), sizeof(reuse));

      if (err == -1) throw errno;

      local_info_.sin_family      = AF_INET;
      local_info_.sin_port        = htons(port);
      local_info_.sin_addr.s_addr = htonl(INADDR_ANY);

      memset(&(local_info_.sin_zero), 0, 8);

      err = bind(socket_, (struct sockaddr*)&local_info_, sizeof(struct sockaddr));

      if (err == -1) throw errno;

      err = listen(socket_, 16);

      if (err == -1) throw errno;
    }
  }
}
