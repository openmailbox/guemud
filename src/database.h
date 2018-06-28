#ifndef GUEMUD_DATABASE_H_
#define GUEMUD_DATABASE_H_

#include <vector>

#include "entity.h"

namespace guemud {

template <typename EntityClass>
class Database {
  public:
    virtual EntityClass& Create() {
      EntityClass* entity = new EntityClass();

      entity->SetId(next_id_++);

      loaded_.push_back(entity);

      return *entity;
    };

    EntityClass* First() {
      if (loaded_.size() == 0) return 0;

      return loaded_.at(0);
    }
    EntityClass& Load(EntityId id);
  protected:
    std::vector<EntityClass*> loaded_;
    EntityId                 next_id_ = 1; // temporary
};

}

#endif
