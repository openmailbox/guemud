#include "connection.h"

guemud::Connection::Connection(int socket) : socket_(socket) {}

int guemud::Connection::GetSocket() const { return socket_; }

bool guemud::Connection::Compare::operator()(const Connection* lhs, const Connection* rhs) {
  return lhs->GetSocket() < rhs->GetSocket();
}

void guemud::Connection::BufferData(const char* buffer, int buffer_size) {
  buffer_out_.append(buffer, buffer_size);
}

int guemud::Connection::Receive() {
  int bytes = recv(socket_, buffer_in_, kBufferSize, 0);

  telnet_.Translate(*this, buffer_in_, bytes);

  return bytes;
}

int guemud::Connection::SendBuffer() {
  if (buffer_out_.size() == 0) return 0;

  int bytes = send(socket_, buffer_out_.data(), (int)buffer_out_.size(), 0);

  buffer_out_.erase(0, bytes);

  return bytes;
}
