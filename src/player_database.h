#ifndef GUEMUD_PLAYER_DATABASE_H_
#define GUEMUD_PLAYER_DATABASE_H_

#include "database.h"
#include "player.h"

namespace guemud {

class PlayerDatabase : public Database<Player> {
  public:
    std::vector<Player*> GetConnected();
};

extern PlayerDatabase PlayerDB;

}

#endif
