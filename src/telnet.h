#ifndef GUEMUD_TELNET_H_
#define GUEMUD_TELNET_H_

#include <string.h>

#include <iostream>

namespace guemud {
  class Connection; // forward declaration

  class Telnet {
    public:
      static const int kBufferSize = 1024;

      Telnet();
      void Translate(Connection& conn, char* buffer, int buffer_size);

    private:
      char buffer_in_[kBufferSize];
      int  buffer_in_size_;
  };
}

#endif
