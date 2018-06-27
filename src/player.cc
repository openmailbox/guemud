#include "player.h"

namespace guemud {

Player::Player(networking::Connection* connection, std::string name) :
  Entity(), connection_(connection) {
    SetName(name);
  }

networking::Connection* Player::GetConnection() { return connection_; }

}
