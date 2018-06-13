#include <time.h>

#include <iostream>

#include "game.h"

int main() {
  guemud::Game game;

  struct timespec loop_time, loop_remain;
  loop_time.tv_nsec = 1000;

  std::cout << "Starting GueMUD..." << std::endl;

  while (game.IsRunning()) {
    // process input
    game.ExecuteLoop();
    nanosleep(&loop_time, &loop_remain); // yield thread to OS
  }

  std::cout << "Exited!" << std::endl;

  return 0;
}
