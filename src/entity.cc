#include "entity.h"

namespace guemud {
  Entity::Entity() : id_(0) {}

  std::vector<Entity::Reference>::iterator guemud::Entity::BeginContents() {
    return contents_.begin();
  }

  std::vector<Entity::Reference>::iterator guemud::Entity::EndContents() {
    return contents_.end();
  }

  void Entity::AddEntity(Entity& new_entity) {
    Entity::Reference ref;

    ref.id = new_entity.GetId();
    ref.type = typeid(new_entity).name();

    contents_.push_back(ref);
  }

  int Entity::GetAttribute(std::string name) { return attributes_.at(name); }

  std::string Entity::GetDescription() { return description_; }

  EntityId Entity::GetId() { return id_; }

  Entity::Reference Entity::GetLocation() { return location_; }

  std::string Entity::GetName() { return name_; }

  void Entity::Remove(Entity& entity) {
    std::vector<Entity::Reference>::iterator itr = BeginContents();

    while (itr != EndContents()) {
      if (entity.GetId() == itr->id) {
        contents_.erase(itr);
        return;
      }

      itr++;
    }
  }

  void Entity::Remove(Entity::Reference reference) {
    std::vector<Entity::Reference>::iterator itr = BeginContents();

    while (itr != EndContents()) {
      if (reference.id == itr->id) {
        contents_.erase(itr);
        return;
      }

      itr++;
    }
  }

  void Entity::SetAttribute(std::string name, int value) {
    attributes_.insert(std::make_pair(name, value));
  }

  void Entity::SetDescription(std::string desc) { description_ = desc; }

  void Entity::SetId(EntityId id) { id_ = id; }

  void guemud::Entity::SetLocation(Entity::Reference new_location) {
    location_ = new_location;
  }

  void guemud::Entity::SetLocation(Entity& new_location) {
    location_.id = new_location.GetId();
    location_.type = typeid(new_location).name();
  }

  void Entity::SetName(std::string name) { name_ = name; }
}
