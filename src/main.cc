#include <time.h>

#include <csignal>
#include <iostream>

#include "database/cache.h"
#include "game.h"
#include "logger.h"
#include "networking/connection_manager.h"
#include "networking/listening_manager.h"

guemud::Game game;

void Cleanup() {
  guemud::SystemLog.Log("Shutting down...");

  // TODO: Close sockets, etc.

#ifdef WIN32
  WSACleanup();
#endif
}

void HandleSignal(int signum) {
  switch (signum) {
    case SIGINT:
      guemud::SystemLog.Log("Signal " + std::to_string(signum) +
                            " (SIGINT) received.");
      game.Stop();
      break;
#ifndef WIN32
    case SIGHUP:
      guemud::SystemLog.Log("Signal " + std::to_string(signum) +
                            " (SIGHUP) received.");
      break;
#endif
    case SIGTERM:
      guemud::SystemLog.Log("Signal " + std::to_string(signum) +
                            " (SIGTERM) received.");
      game.Stop();
      break;
    default:
      guemud::SystemLog.Log("Signal " + std::to_string(signum) +
                            " (SIGQUIT) received.");
      break;
  }
}

int main() {
  guemud::SystemLog.Log("Starting GueMUD...");

  guemud::database::RoomDB.Initialize();
  guemud::database::RoomDB.Load(3); // temporary

  signal(SIGINT, HandleSignal);

#ifdef WIN32
  WSADATA winsockdata;
  WSAStartup(MAKEWORD(2, 2), &winsockdata);
#else
  struct timespec loop_time, loop_remain;
  loop_time.tv_nsec = 1000;
  loop_time.tv_sec = 0;
#endif
  guemud::networking::ConnectionManager connection_manager;
  guemud::networking::ListeningManager listening_manager(4040,
                                                         connection_manager);

  while (game.IsRunning()) {
    listening_manager.Listen();
    connection_manager.Manage();
    game.ExecuteLoop();
#ifdef WIN32
    Sleep(1);
#else
    nanosleep(&loop_time, &loop_remain);  // yield thread to OS
#endif
  }

  Cleanup();

  guemud::SystemLog.Log("Exited");

  return 0;
}
