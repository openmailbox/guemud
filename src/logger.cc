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
  char time_buffer[256];
  time_t t;
  time(&t);
  struct tm* info = localtime(&t);
  strftime(time_buffer, 256, "%D - %T", info);

  file << "[" << time_buffer << "] " << message << std::endl;
  std::cout << "[" << time_buffer << "] " << message << std::endl;
}

}