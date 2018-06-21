#ifndef GUEMUD_CONNECTION_H_
#define GUEMUD_CONNECTION_H_

#include <sys/socket.h>
#include <sys/types.h>

#include <stack>

#include "connection_handler.h"
#include "telnet.h"

namespace guemud {
  class Connection {
    public:
      static const int kBufferSize = 1024;

      struct Compare {
        bool operator()(const Connection* lhs, const Connection* rhs);
      };

      std::string name; // temporary

      Connection(int socket);

      void               AddHandler(ConnectionHandler* handler);
      void               BufferData(const char* buffer, int buffer_size);
      ConnectionHandler* GetHandler();
      Telnet*            GetProtocol();
      int                GetSocket() const;
      int                Receive();
      void               RemoveHandler();
      int                SendBuffer();
    private:
      char                           buffer_in_[kBufferSize];
      std::string                    buffer_out_;
      std::stack<ConnectionHandler*> handlers_;
      int                            socket_;
      Telnet                         telnet_;
  };
}

#endif
