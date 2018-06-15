#include "connection_manager.h"

guemud::ConnectionManager::ConnectionManager() {
  FD_ZERO(&socket_set_);
  FD_ZERO(&activity_set_);
}

void guemud::ConnectionManager::Manage() {
  if (sockets_.size() == 0) return;

  struct timeval zerotime;
  zerotime.tv_usec = 100;
  zerotime.tv_sec = 0;
  activity_set_ = socket_set_;

  int err = select(*(sockets_.rbegin()) + 1, &activity_set_, NULL, NULL, &zerotime);

  if (err == -1) throw errno;
  if (err < 1) return;

  char buffer[1024];
  std::set<int>::iterator itr = sockets_.begin();
  std::set<int>::iterator current;

  while (itr != sockets_.end()) {
    current = itr++;

    if (!FD_ISSET(*current, &activity_set_)) continue;

    int err = recv(*current, buffer, 1024, 0);

    if (err == -1) throw errno;
    
    if (err == 0) {
      FD_CLR(*current, &socket_set_);
      sockets_.erase(current);
      shutdown(*current, SHUT_RDWR);
    }

    std::cout << "Message: " << buffer << std::endl;
  }
}

void guemud::ConnectionManager::NewConnection(int socket) {
  std::cout << "New connection " << socket << std::endl;

  FD_SET(socket, &socket_set_);

  sockets_.insert(socket);
}
