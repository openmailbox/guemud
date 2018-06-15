#include "listening_manager.h"

guemud::ListeningManager::ListeningManager(int port, ConnectionManager manager)
  : connection_manager_(manager),
    port_(port) {
  socket_  = ListeningSocket();
  socket_.Listen(port_);
};

void guemud::ListeningManager::Listen() {
  struct sockaddr_in new_socket_addr;
  socklen_t new_socket_size = sizeof(new_socket_addr);

  int new_socket = accept(socket_.GetSocket(), (struct sockaddr*)&new_socket_addr, &new_socket_size);

  if (new_socket == -1) {
    if (errno != EWOULDBLOCK && errno != EAGAIN) {
      throw errno;
    }
  }
}
