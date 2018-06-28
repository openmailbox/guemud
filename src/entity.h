#ifndef GUEMUD_ENTITY_H_
#define GUEMUD_ENTITY_H_

#include <string>
#include <vector>

namespace guemud {
  typedef unsigned int EntityId;

  enum class EntityType {
    Player,
    Room
  };

  class Entity {
    public:
      Entity();

      std::string GetDescription();
      EntityId    GetId();
      std::string GetName();
      void        SetDescription(std::string desc);
      void        SetId(EntityId id);
      void        SetLocation(Entity& entity);
      void        SetName(std::string name);
    protected:
      std::vector<Entity*> contents_;
      std::string          description_;
      EntityId             id_;
      std::string          name_;
      EntityId             location_id_;
      EntityType           location_type_;
  };
}

#endif
