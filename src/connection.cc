#include "connection.h"

guemud::Connection::Connection(int socket) : socket_(socket) {}

int guemud::Connection::GetSocket() const { return socket_; }

bool guemud::Connection::Compare::operator()(const Connection* lhs, const Connection* rhs) {
  return lhs->GetSocket() < rhs->GetSocket();
}

int guemud::Connection::Receive() {
  int bytes = recv(socket_, buffer_in_, kBufferSize, 0);

  telnet_.Translate(*this, buffer_in_, bytes);

  return bytes;
}
