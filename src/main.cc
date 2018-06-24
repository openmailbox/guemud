#include <stdlib.h>
#include <time.h>

#include <csignal>
#include <iostream>

#include "game.h"
#include "networking/connection_manager.h"
#include "networking/listening_manager.h"

void HandleSignal(int signum) {
  std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

  // cleanup

  exit(signum);
}

int main() {
  try {
    signal(SIGINT, HandleSignal);

    std::cout << "Starting GueMUD..." << std::endl;

    #ifdef WIN32
      WSADATA winsockdata;
      WSAStartup(MAKEWORD(2, 2), &winsockdata);
    #else
      struct timespec loop_time, loop_remain;
      loop_time.tv_nsec = 1000;
      loop_time.tv_sec  = 0;
    #endif

    guemud::Game game;
    guemud::networking::ConnectionManager connection_manager;
    guemud::networking::ListeningManager listening_manager(4040, connection_manager);

    while (game.IsRunning()) {
      listening_manager.Listen();
      connection_manager.Manage();
      game.ExecuteLoop();
   	  #ifdef WIN32
	    Sleep(1);
  	  #else
	    nanosleep(&loop_time, &loop_remain); // yield thread to OS
  	  #endif
    }

  } catch (int e) {
    std::cout << "An exception occurred: " << e << std::endl;
  } catch (...) {
    std::cout << "An exception occurred." << std::endl;
  }

  #ifdef WIN32
    WSACleanup();
  #endif

  std::cout << "Exited." << std::endl;

  return 0;
}
