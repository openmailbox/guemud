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
      int new_socket = accept4(socket_.GetSocket(), (struct sockaddr*)&new_socket_addr, &new_socket_size, SOCK_NONBLOCK);

      if (new_socket == -1) {
        if (errno != EWOULDBLOCK && errno != EAGAIN) throw errno;

        return;
      }

      connection_manager_.NewConnection(new_socket);
    }
  }
}
