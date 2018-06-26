#include "listening_socket.h"

namespace guemud {
  namespace networking {
    void guemud::networking::ListeningSocket::CheckErrors(int result) {
      if (result != -1) return;

      #ifdef WIN32
        int error = WSAGetLastError();
        if (error != WSAEWOULDBLOCK) throw guemud::Error(error);
      #else
        if (errno != EWOULDBLOCK && errno != EAGAIN) throw guemud::Error(errno);
      #endif
    }

    void ListeningSocket::Listen( int port ) {
      #ifdef WIN32
        socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (socket_ == INVALID_SOCKET) CheckErrors(-1);
      #else
        socket_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
        CheckErrors(socket_);
      #endif

      #ifdef WIN32
        unsigned long mode = 1;
        int err = ioctlsocket(socket_, FIONBIO, &mode);
        CheckErrors(err);
      #endif

      int reuse = 1;
      int err = setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, (char*)(&reuse), sizeof(reuse));

      CheckErrors(err);

      local_info_.sin_family      = AF_INET;
      local_info_.sin_port        = htons(port);
      local_info_.sin_addr.s_addr = htonl(INADDR_ANY);

      memset(&(local_info_.sin_zero), 0, 8);

      err = bind(socket_, (struct sockaddr*)&local_info_, sizeof(struct sockaddr));

      CheckErrors(err);

      err = listen(socket_, 16);

      CheckErrors(err);
    }
  }
}
