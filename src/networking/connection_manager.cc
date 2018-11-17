#include "connection_manager.h"

namespace guemud {
  namespace networking {
    ConnectionManager::ConnectionManager() {
      FD_ZERO(&socket_set_);
      FD_ZERO(&activity_set_);
    }

    void ConnectionManager::CheckErrors(int result) {
      if (result != -1) return;

      #ifdef WIN32
        int error = WSAGetLastError();
        if (error != WSAEWOULDBLOCK) throw guemud::Error(error);
      #else
        if (errno != EWOULDBLOCK && errno != EAGAIN) throw guemud::Error(errno);
      #endif
    }

    void ConnectionManager::Close(Connection* connection) {
      #ifdef WIN32
        int shutdown_method = SD_BOTH;
      #else
        int shutdown_method = SHUT_RDWR;
      #endif

      guemud::SystemLog.Log("Shutting down " + std::to_string(connection->GetSocket()));
      FD_CLR(connection->GetSocket(), &socket_set_);
      shutdown(connection->GetSocket(), shutdown_method);
      connections_.erase(connection);
      delete connection;
    }

    void ConnectionManager::CloseConnections() {
      std::set<Connection*>::iterator itr = connections_.begin();
      std::set<Connection*>::iterator current;

      while (itr != connections_.end()) {
        current = itr++;

        if ((*current)->IsClosing()) {
          Close(*current);
        }
      }
    }

    void ConnectionManager::Listen() {
      if (connections_.size() == 0) return;

      struct timeval zerotime;
      zerotime.tv_usec = 100;
      zerotime.tv_sec = 0;
      activity_set_ = socket_set_;

      int err = select((*(connections_.rbegin()))->GetSocket() + 1, &activity_set_, NULL, NULL, &zerotime);

      CheckErrors(err);

      if (err == 0) return; // no activity on any sockets

      std::set<Connection*>::iterator itr = connections_.begin();
      std::set<Connection*>::iterator current;

      while (itr != connections_.end()) {
        current = itr++;

        if (!FD_ISSET((*current)->GetSocket(), &activity_set_)) continue;

        int err = (*current)->Receive();

        CheckErrors(err);

        if (err == 0) {
          Close(*current);
        }
      }
    }

    void ConnectionManager::Manage() {
      Listen();
      Send();
      CloseConnections();
    }

    void ConnectionManager::NewConnection(int socket) {
      Connection* conn = new Connection(socket);

      guemud::SystemLog.Log("New connection " + std::to_string(socket));

      FD_SET(socket, &socket_set_);

      connections_.insert(conn);
      conn->AddHandler(new guemud::handlers::Logon(conn));
    }

    void ConnectionManager::Send() {
      std::set<Connection*>::iterator itr = connections_.begin();
      std::set<Connection*>::iterator current;

      while (itr != connections_.end()) {
        current = itr++;

        int err = (*current)->SendBuffer();

        CheckErrors(err);
      }
    }
  }
}
