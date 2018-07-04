#pragma once

#include <vector>

#include "entity.h"
#include "logger.h"
#include "player.h"
#include "room.h"
#include "sqlite3.h"

namespace guemud {

template <class EntityType>
class Database {
 public:
  typename std::vector<EntityType*>::iterator Begin() { return cache_.begin(); }
  typename std::vector<EntityType*>::iterator End() { return cache_.end(); }

  EntityType* Create() {
    EntityType* entity = new EntityType();

    entity->SetId(next_id_++);

    cache_.push_back(entity);

    return entity;
  }

  // TODO: Don't need a separate connection for each subclass
  void Initialize() { 
    int err = sqlite3_open(kDatabaseFile.data(), &db);

    if (err != SQLITE_OK) {
      std::string msg = sqlite3_errmsg(db);
      SystemLog.Log("Unable to open database: " + msg);
      sqlite3_close(db);
      throw msg;
    }
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
  static const std::string kDatabaseFile;

  std::vector<EntityType*> cache_;
  sqlite3*                 db;
  EntityId                 next_id_ = 1;  // TODO: Replace w/ DB primary key
};

template <class EntityType>
const std::string Database<EntityType>::kDatabaseFile = "data/guemud.sqlite3"; // TODO: Configuration

extern Database<Player> PlayerDB;
extern Database<Room> RoomDB;

}  // namespace guemud
