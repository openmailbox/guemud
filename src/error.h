#ifndef GUEMUD_ERROR_H_
#define GUEMUD_ERROR_H_

#include <exception>
#include <map>
#include <string>

namespace guemud {
  class Error : public std::exception {
    public:
      static const std::map<int, std::string> kErrorCodes;

      Error(int code);

      const char* what() const throw();
    private:
      std::string message_;
  };
}


#endif
