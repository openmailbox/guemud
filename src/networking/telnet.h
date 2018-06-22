#ifndef GUEMUD_NETWORKING_TELNET_H_
#define GUEMUD_NETWORKING_TELNET_H_

#include <string.h>

#include <iostream>

namespace guemud {
  namespace networking {
    class Connection; // forward declaration

    class Telnet {
      public:
        static const int kBufferSize = 1024;

        Telnet();
        void SendString(Connection& conn, std::string string);
        void Translate(Connection& conn, char* buffer, int buffer_size);
      private:
        char buffer_in_[kBufferSize];
        int  buffer_in_size_;
    };
  }
}

#endif
