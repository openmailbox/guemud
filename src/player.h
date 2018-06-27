#ifndef GUEMUD_PLAYER_H_
#define GUEMUD_PLAYER_H_

#include "entity.h"
#include "networking/connection.h"

namespace guemud {
  class Player : public Entity {
    public:
      Player(networking::Connection* connection, std::string name);

      networking::Connection* GetConnection();
    private:
      networking::Connection* connection_;
  };
}

#endif
