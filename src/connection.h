#ifndef GUEMUD_CONNECTION_H_
#define GUEMUD_CONNECTION_H_

#include <errno.h>
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

      void BufferData(const char* buffer, int buffer_size);
      int  GetSocket() const;
      int  Receive();
      void SendBuffer();
    private:
      char        buffer_in_[kBufferSize];
      std::string buffer_out_;
      int         socket_;
      Telnet      telnet_;
  };
}

#endif
