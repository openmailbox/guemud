#include <stdlib.h>
#include <time.h>

#include <csignal>
#include <exception>
#include <iostream>

#include "game.h"
#include "networking/connection_manager.h"
#include "networking/listening_manager.h"

void Cleanup() {
  std::cout << "Shutting down." << std::endl;

  #ifdef WIN32
    WSACleanup();
  #endif
}

void HandleSignal(int signum) {
  std::cout << "Signal (" << signum << ") received." << std::endl;
  throw "Signal " + std::to_string(signum);
}

int main() {
  std::cout << "Starting GueMUD..." << std::endl;

  try {
    signal(SIGINT, HandleSignal);

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

  } catch (std::exception& e) {
    std::cerr << "An exception occurred: " << e.what() << std::endl;
    Cleanup();
    return 1;
  } catch (const char* msg) {
    std::cerr << "An exception occurred: " << msg << std::endl;
    Cleanup();
    return 1;
  } catch (int e) {
    std::cerr << "An exception occurred: " << e << std::endl;
    Cleanup();
    return 1;
  } catch (...) {
    std::cerr << "An exception occurred." << std::endl;
    Cleanup();
    return 1;
  }

  Cleanup();

  return 0;
}
