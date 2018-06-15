#include <stdlib.h>
#include <time.h>

#include <csignal>
#include <iostream>

#include "game.h"
#include "connection_manager.h"
#include "listening_manager.h"

void HandleSignal(int signum) {
  std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

  // cleanup

  exit(signum);
}

int main() {
  try {
    signal(SIGINT, HandleSignal);

    guemud::Game game;
    guemud::ConnectionManager connection_manager;
    guemud::ListeningManager listening_manager(4040, connection_manager);

    struct timespec loop_time, loop_remain;
    loop_time.tv_nsec = 1000;
    loop_time.tv_sec  = 0;

    std::cout << "Starting GueMUD..." << std::endl;

    while (game.IsRunning()) {
      listening_manager.Listen();
      connection_manager.Manage();
      game.ExecuteLoop();
      nanosleep(&loop_time, &loop_remain); // yield thread to OS
    }

  } catch (int e) {
    std::cout << "An exception occurred: " << e << std::endl;
  } catch (...) {
    std::cout << "An exception occurred." << std::endl;
  }

  std::cout << "Exited." << std::endl;

  return 0;
}
