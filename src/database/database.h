#pragma once

#include <sstream>
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
  // TODO: Cleanup/shutdown
  void Initialize() {
    int err = sqlite3_open(kDatabaseFile.data(), &db_);

    if (err != SQLITE_OK) {
      std::string msg = sqlite3_errmsg(db_);
      SystemLog.Log("Unable to open database: " + msg);
      sqlite3_close(db_);
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

    // If we got here, there was no cached result
    std::string query = "SELECT id, name, description FROM rooms LIMIT 1";
    char* error_message = 0;

    int err =
        sqlite3_exec(db_, query.data(), LoadRowCallback, 0, &error_message);

    if (err != SQLITE_OK) {
      SystemLog.Log("SQL error: " + (std::string)error_message);
      sqlite3_free(error_message);
    }

    return NULL;
  }

 protected:
  static const std::string kDatabaseFile;

  std::vector<EntityType*> cache_;
  sqlite3* db_;
  EntityId next_id_ = 1;  // TODO: Replace w/ DB primary key

  static int LoadRowCallback(void* unused, int column_count, char** values,
                             char** columns) {
    std::stringstream msg;
    msg << "Loaded " << typeid(EntityType).name() << " - ";

    for (int i = 0; i < column_count; i++) {
      msg << columns[i] << " = " << values[i];
      if (i < column_count - 1) msg << " | ";
    }

    SystemLog.Log(msg.str());

    return 0;
  }
};

template <class EntityType>
const std::string Database<EntityType>::kDatabaseFile =
    "data/guemud.sqlite3";  // TODO: Configuration

extern Database<Player> PlayerDB;
extern Database<Room> RoomDB;

}  // namespace guemud
