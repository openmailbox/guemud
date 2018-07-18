#pragma once

#include <sstream>
#include <typeinfo>
#include <vector>

#include "../entity.h"
#include "../logger.h"
#include "../player.h"
#include "../room.h"
#include "sqlite_adapter.h"

namespace guemud {
namespace database {

template <class EntityType>
class Cache {
 public:
  typename std::vector<EntityType*>::iterator Begin() { return cache_.begin(); }
  typename std::vector<EntityType*>::iterator End() { return cache_.end(); }

  Cache(std::string table_name) : table_name_(table_name) {}

  void Initialize() { adapter_.Initialize(); }

  EntityType* Create() {
    EntityType* entity = new EntityType();

    entity->SetId(next_id_++);

    cache_.push_back(entity);

    return entity;
  }

  EntityType* First() {
    std::string query = "SELECT * FROM " + table_name_ + " LIMIT 1";
    LoadFromDatabase(query);
    return *(Begin());
  }

  EntityType* Load(EntityId id) {
    EntityType* entity = FindFromCache(id);

    if (entity == NULL) {
      std::string query =
        "select * from " + table_name_ + " where id = " + std::to_string(id);
      LoadFromDatabase(query);
      entity = FindFromCache(id);
    }

    return entity;
  }

  void Shutdown() { adapter_.Shutdown(); }

 protected:
  SqliteAdapter            adapter_;
  std::vector<EntityType*> cache_;
  EntityId                 next_id_ = 1;  // TODO: Replace w/ DB primary key
  std::string              table_name_;

  EntityType* FindFromCache(EntityId id) {
    typename std::vector<EntityType*>::iterator itr = cache_.begin();

    while (itr != cache_.end()) {
      EntityType* next = *itr;

      if (id == next->GetId()) return next;

      itr++;
    }

    return NULL;
  }

  void LoadFromDatabase(std::string query) {
    DatabaseRow row;
    SqliteCursor cursor = adapter_.Prepare(query);

    while (!cursor.IsFinished()) {
      std::stringstream msg;

      DatabaseRow row    = cursor.GetCurrentRow();
      EntityType* entity = new EntityType();

      // TODO: Put remaining arbitrary attributes in the Entity attributes map
      entity->SetId(std::stoi(row.at("id")));
      entity->SetName(row.at("name"));
      entity->SetDescription(row.at("description"));

      cache_.push_back(entity);

      msg << "LOAD " << typeid(entity).name() << " " << entity->GetId();
      SystemLog.Log(msg.str());

      cursor.Next();
    }
  }
};

extern Cache<Player> PlayerDB;
extern Cache<Room> RoomDB;

}  // namespace database
}  // namespace guemud
