#include "game.h"

guemud::Game::Game() {
  is_running_ = true;
}

void guemud::Game::ExecuteLoop() {
  // perform actions
}

bool guemud::Game::IsRunning() { return is_running_; }
