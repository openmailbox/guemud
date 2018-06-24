#include "listening_manager.h"

namespace guemud {
  namespace networking {
    ListeningManager::ListeningManager(int port, ConnectionManager& manager)
      : connection_manager_(manager),
      port_(port) {
        socket_  = ListeningSocket();
        socket_.Listen(port_);
      };

    void ListeningManager::Listen() {
      struct sockaddr_in new_socket_addr;
      socklen_t new_socket_size = sizeof(new_socket_addr);

      // TODO: Use select()
      #ifdef WIN32
        unsigned long mode = 1;
        int new_socket = accept(socket_.GetSocket(), (struct sockaddr*)&new_socket_addr, &new_socket_size);
        if (new_socket != -1) ioctlsocket(new_socket, FIONBIO, &mode);
      #else
        int new_socket = accept4(socket_.GetSocket(), (struct sockaddr*)&new_socket_addr, &new_socket_size, SOCK_NONBLOCK);
      #endif

      if (new_socket == -1) {
        #ifdef WIN32
          int error = WSAGetLastError();
          if (error != WSAEWOULDBLOCK) throw error;
        #else
          if (errno != EWOULDBLOCK && errno != EAGAIN) throw errno;
        #endif

        return;
      }

      connection_manager_.NewConnection(new_socket);
    }
  }
}
