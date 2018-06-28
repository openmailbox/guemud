#pragma once

#include "entity.h"

namespace guemud {

class Room : public Entity {
 public:
  static const EntityType kType = EntityType::Room;
};

}  // namespace guemud
