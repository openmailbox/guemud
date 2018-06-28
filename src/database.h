#ifndef GUEMUD_DATABASE_H_
#define GUEMUD_DATABASE_H_

#include <vector>

#include "entity.h"

namespace guemud {

template <typename EntityType>
class Database {
  public:
    virtual EntityType& Create() {
      EntityType* entity = new EntityType();

      entity->SetId(next_id_++);

      loaded_.push_back(entity);

      return *entity;
    };

    EntityType& Load(EntityId id);
  protected:
    std::vector<EntityType*> loaded_;
    EntityId                 next_id_ = 1; // temporary
};

}

#endif
