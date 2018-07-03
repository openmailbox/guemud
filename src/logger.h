#pragma once

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

namespace guemud {

class Logger {
 public:
  static const std::string kLogFile;

  Logger(const std::string file_name);
  ~Logger();

  void Log(std::string message);

 private:
  std::fstream file;
};

extern Logger SystemLog;

}  // namespace guemud
