#include "connection_manager.h"

namespace guemud {
  namespace networking {
    ConnectionManager::ConnectionManager() {
      FD_ZERO(&socket_set_);
      FD_ZERO(&activity_set_);
    }

    void ConnectionManager::Listen() {
      if (connections_.size() == 0) return;

      struct timeval zerotime;
      zerotime.tv_usec = 100;
      zerotime.tv_sec = 0;
      activity_set_ = socket_set_;

      int err = select((*(connections_.rbegin()))->GetSocket() + 1, &activity_set_, NULL, NULL, &zerotime);

      if (err == -1) throw errno; if (err < 1) return;

      std::set<Connection*>::iterator itr = connections_.begin();
      std::set<Connection*>::iterator current;

      while (itr != connections_.end()) {
        current = itr++;

        if (!FD_ISSET((*current)->GetSocket(), &activity_set_)) continue;

        int err = (*current)->Receive();

        if (err == -1) throw errno;

        if (err == 0) {
          int shutdown_method;
          #ifdef WIN32
            shutdown_method = SD_BOTH;
          #else
            shutdown_method = SHUT_RDWR
          #endif

          std::cout << "Shutting down " << (*current)->GetSocket() << std::endl;
          FD_CLR((*current)->GetSocket(), &socket_set_);
          shutdown((*current)->GetSocket(), shutdown_method);
          connections_.erase(current);
          delete *current;
        }
      }
    }

    void ConnectionManager::Manage() {
      Listen();
      Send();
    }

    void ConnectionManager::NewConnection(int socket) {
      Connection* conn = new Connection(socket);

      std::cout << "New connection " << socket << std::endl;

      FD_SET(socket, &socket_set_);

      connections_.insert(conn);
      conn->AddHandler(new guemud::Logon(conn));
    }

    void ConnectionManager::Send() {
      std::set<Connection*>::iterator itr = connections_.begin();
      std::set<Connection*>::iterator current;

      while (itr != connections_.end()) {
        current = itr++;

        int bytes = (*current)->SendBuffer();

        if (bytes == -1) throw errno;
      }
    }
  }
}