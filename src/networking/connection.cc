#include "connection.h"

namespace guemud {
  namespace networking {
    Connection::Connection(int socket) : socket_(socket) {
      memset(buffer_in_, 0, sizeof buffer_in_);
    }

    void Connection::AddHandler(ConnectionHandler* handler) {
      handlers_.push(handler);
      handler->Enter();
    }

    void Connection::BufferData(const char* buffer, int buffer_size) {
      buffer_out_.append(buffer, buffer_size);
    }

    void Connection::Close() { closing_ = true; }

    ConnectionHandler* Connection::GetHandler() {
      if (handlers_.size() == 0) return 0;

      return handlers_.top();
    }

    Telnet* Connection::GetProtocol() { return &telnet_; }

    int Connection::GetSocket() const { return socket_; }

    bool Connection::IsClosing() const { return closing_; }

    bool Connection::Compare::operator()(const Connection* lhs, const Connection* rhs) const {
      return lhs->GetSocket() < rhs->GetSocket();
    }

    int Connection::Receive() {
      int bytes = recv(socket_, buffer_in_, kBufferSize, 0);

      telnet_.Translate(*this, buffer_in_, bytes);

      return bytes;
    }

    void Connection::RemoveHandler() {
      if (handlers_.size() == 0) return;

      ConnectionHandler* handler = handlers_.top();
      handlers_.pop();
      delete handler;

      if (handlers_.size() > 0) handlers_.top()->Enter();
    }

    int Connection::SendBuffer() {
      if (buffer_out_.size() == 0) return 0;

      int bytes = send(socket_, buffer_out_.data(), (int)buffer_out_.size(), 0);

      buffer_out_.erase(0, bytes);

      return bytes;
    }
  }
}
