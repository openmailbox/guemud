#ifndef GUEMUD_DATABASE_H_
#define GUEMUD_DATABASE_H_

#include <vector>

#include "entity.h"

namespace guemud {

class Database {
  public:
    std::vector<Entity*>::iterator Begin();
    Entity*                        Create();
    std::vector<Entity*>::iterator End();
    Entity*                        First();
    Entity*                        Load(Entity::Reference ref);
  protected:
    std::vector<Entity*> cache_;
    EntityId             next_id_ = 1; // TODO: Replace w/ DB primary key
};

extern Database PlayerDB;
extern Database RoomDB;

}

#endif
