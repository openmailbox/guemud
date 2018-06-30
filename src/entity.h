#ifndef GUEMUD_ENTITY_H_
#define GUEMUD_ENTITY_H_

#include <string>
#include <typeinfo>
#include <vector>

namespace guemud {

typedef unsigned int EntityId;

class Entity {
  public:
    struct Reference {
      EntityId    id;
      std::string type; // obtained from typeid(entity).name()
    };

    Entity();

    std::vector<Entity::Reference>::iterator BeginContents();
    std::vector<Entity::Reference>::iterator EndContents();

    void              AddEntity(Entity& new_entity);
    std::string       GetDescription();
    EntityId          GetId();
    Entity::Reference GetLocation();
    std::string       GetName();
    void              SetDescription(std::string desc);
    void              SetId(EntityId id);
    void              SetLocation(Entity::Reference new_location);
    void              SetLocation(Entity& new_location);
    void              SetName(std::string name);
  protected:
    std::vector<Entity::Reference> contents_;
    std::string                    description_;
    EntityId                       id_;
    std::string                    name_;
    Entity::Reference              location_;
};

}

#endif
