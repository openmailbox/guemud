#include "player.h"

namespace guemud {
  networking::Connection* Player::GetConnection() { return connection_; }
}
