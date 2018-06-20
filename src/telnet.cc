#include "telnet.h"
#include "connection.h"

guemud::Telnet::Telnet::Telnet() { buffer_in_size_ = 0; }

void guemud::Telnet::Translate(Connection &conn, char* buffer, int buffer_size) {
  for (int i = 0; i < buffer_size; i++) {
    char next_character = buffer[i];

    if (next_character >= 32 && next_character != 127) {
      buffer_in_[buffer_in_size_] = next_character;
      buffer_in_size_++;
    } else if (next_character == 8 && buffer_in_size_ > 0) {
      buffer_in_size_--;
    } else if (next_character == '\n' || next_character == '\r') {
      if (buffer_in_size_ > 0) {
        std::cout << "Message from " << conn.GetSocket() << ": " << buffer_in_ << std::endl;
        memset(buffer_in_, 0, buffer_in_size_);
        buffer_in_size_ = 0;
      }
    }
  }
}

