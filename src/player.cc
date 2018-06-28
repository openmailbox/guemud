#include "player.h"

namespace guemud {

Player::Player() {}

Player::Player(networking::Connection* connection, std::string name) :
  Entity(), connection_(connection) {
    SetName(name);
  }

networking::Connection* Player::GetConnection() { return connection_; }

void Player::SetConnection(networking::Connection& conn) { connection_ = &conn; }

}
