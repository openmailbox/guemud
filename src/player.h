#ifndef GUEMUD_PLAYER_H_
#define GUEMUD_PLAYER_H_

#include "entity.h"
#include "networking/connection.h"

namespace guemud {
  class Player : public Entity {
    public:
      Player(networking::Connection* connection, std::string name);

      networking::Connection* GetConnection();
      std::string             GetName();
    private:
      networking::Connection* connection_;
      std::string             name_;
  };
}

#endif
