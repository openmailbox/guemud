#include "database.h"

namespace guemud {

Database PlayerDB;
Database RoomDB;

std::vector<Entity*>::iterator Database::Begin() {
  return cache_.begin();
}

Entity* Database::Create() {
  Entity* entity = new Entity();

  entity->SetId(next_id_++);

  cache_.push_back(entity);

  return entity;
};

std::vector<Entity*>::iterator Database::End() {
  return cache_.end();
}

Entity* Database::First() {
  if (cache_.size() == 0) return 0;

  return cache_.at(0);
}

Entity* Database::Load(Entity::Reference ref) {
  std::vector<Entity*>::iterator itr = cache_.begin();

  while (itr != cache_.end()) {
    Entity* next = (*itr)++;

    if (ref.id == next->GetId()) return next;
  }

  return NULL;
}

}
