#include "connection.h"

guemud::Connection::Connection(int socket) : socket_(socket) {}

int guemud::Connection::GetSocket() const { return socket_; }

bool guemud::Connection::Compare::operator()(const Connection& lhs, const Connection& rhs) {
  return lhs.socket_ < rhs.socket_;
}
