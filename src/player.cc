#include "player.h"

namespace guemud {
  Player::Player(networking::Connection* connection, std::string name) : 
    connection_(connection), name_(name) {}

  networking::Connection* Player::GetConnection() { return connection_; }

  std::string Player::GetName() { return name_; }
}
