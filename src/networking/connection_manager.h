#ifndef GUEMUD_NETWORKING_CONNECTION_MANAGER_H_
#define GUEMUD_NETWORKING_CONNECTION_MANAGER_H_

#include <errno.h>
#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/select.h>
#include <sys/socket.h>
#endif

#include <cstddef>
#include <iostream>
#include <set>

#include "../error.h"
#include "../logger.h"
#include "../handlers/logon.h"
#include "connection.h"
#include "connection_manager.h"

namespace guemud {
namespace networking {

class ConnectionManager {
 public:
  ConnectionManager();
  void Close(Connection* connection);
  void Manage();
  void NewConnection(int socket);

 private:
  fd_set socket_set_;
  fd_set activity_set_;
  std::set<Connection*, Connection::Compare> connections_;

  void CheckErrors(int result);
  void CloseConnections();
  void Listen();
  void Send();
};

}  // namespace networking
}  // namespace guemud

#endif
