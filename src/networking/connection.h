#ifndef GUEMUD_NETWORKING_CONNECTION_H_
#define GUEMUD_NETWORKING_CONNECTION_H_


#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include <sys/types.h>

#include <stack>

#include "connection_handler.h"
#include "telnet.h"

namespace guemud {
  namespace networking {
    class Connection {
      public:
        static const int kBufferSize = 1024;

        struct Compare {
          bool operator()(const Connection* lhs, const Connection* rhs) const;
        };

        Connection(int socket);

        void               AddHandler(ConnectionHandler* handler);
        void               BufferData(const char* buffer, int buffer_size);
        void               Close();
        ConnectionHandler* GetHandler();
        Telnet*            GetProtocol();
        int                GetSocket() const;
        bool               IsClosing() const;
        int                Receive();
        void               RemoveHandler();
        int                SendBuffer();
      private:
        char                           buffer_in_[kBufferSize];
        std::string                    buffer_out_;
        bool                           closing_ = false;
        std::stack<ConnectionHandler*> handlers_;
        int                            socket_;
        Telnet                         telnet_;
    };
  }
}

#endif
