#include "player_database.h"

namespace guemud {

PlayerDatabase PlayerDB;

std::vector<Player*> guemud::PlayerDatabase::GetConnected() {
  return loaded_;
}

}