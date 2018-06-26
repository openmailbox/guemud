#include "entity.h"

namespace guemud {
  Entity::Entity() : id_(0) {}

  std::string Entity::GetDescription() { return description_; }

  EntityId Entity::GetId() { return id_; }

  std::string Entity::GetName() { return name_; }

  void Entity::SetDescription(std::string desc) { description_ = desc; }

  void Entity::SetName(std::string name) { name_ = name; }
}
