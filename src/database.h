#pragma once

#include <vector>

#include "entity.h"
#include "player.h"
#include "room.h"

namespace guemud {

template <class EntityType>
class Database {
  public:
    typename std::vector<EntityType*>::iterator Begin() { return cache_.begin(); }
    typename std::vector<EntityType*>::iterator End(){ return cache_.end(); }

    EntityType* Create() {
      EntityType* entity = new EntityType();

      entity->SetId(next_id_++);

      cache_.push_back(entity);

      return entity;
    }

    EntityType* Load(EntityId id) {
      typename std::vector<EntityType*>::iterator itr = cache_.begin();

      while (itr != cache_.end()) {
        EntityType* next = *itr;

        if (id == next->GetId()) return next;

        itr++;
      }

      return NULL;
    }
  protected:
    std::vector<EntityType*> cache_;
    EntityId                 next_id_ = 1; // TODO: Replace w/ DB primary key
};

extern Database<Player> PlayerDB;
extern Database<Room> RoomDB;

}
