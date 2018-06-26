#include "error.h"

namespace guemud {
  #ifdef WIN32
    const std::map<int, std::string> Error::kErrorCodes = {
      {6,     "Specified event object handle is invalid"}, // WSA_INVALID_HANDLE
      {10035, "Resource temporarily unavailable"}          // WSAEWOULDBLOCK
    };
  #else
    const std::map<int, std::string> kErrorCodes = {
      {13, "Permission denied"},    // EACCES
      {35, "Operation would block"} // EWOULDBLOCK
    };
  #endif

  Error::Error(int code) { 
    try {
      message_ = kErrorCodes.at(code);
    } catch (std::out_of_range) {
      message_ = "Unspecified error";
    }
  }

  const char* guemud::Error::what() const throw() { return message_.data(); }
}