#include "logger.h"

namespace guemud {

const std::string Logger::kLogFile = "logs/system.log";

Logger SystemLog(Logger::kLogFile);

Logger::Logger(std::string file_name) { 
  // TODO: Error handling if not successful
  file.open(file_name, std::fstream::in | std::fstream::out | std::fstream::app);
}

Logger::~Logger() { file.close(); }

void guemud::Logger::Log(std::string message) {
  std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();

  const time_t time_string = std::chrono::system_clock::to_time_t(timestamp);
  const int buffer_size = 30;
  char buffer[buffer_size];

  file << "[" << ctime_s(buffer, buffer_size, &time_string) << "] " << message << std::endl;
  std::cout << "[" << ctime_s(buffer, buffer_size, &time_string) << "] " << message << std::endl;
}

}