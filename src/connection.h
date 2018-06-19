#ifndef GUEMUD_CONNECTION_H_
#define GUEMUD_CONNECTION_H_

#include <sys/socket.h>
#include <sys/types.h>

#include "telnet.h"

namespace guemud {
  class Connection {
    public:
      static const int kBufferSize = 1024;

      struct Compare {
        bool operator()(const Connection* lhs, const Connection* rhs);
      };

      Connection(int socket);
      int GetSocket() const;
      int Receive();
    private:
      char   buffer_in_[kBufferSize];
      int    socket_;
      Telnet telnet_;
  };
}

#endif
