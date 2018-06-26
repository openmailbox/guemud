#ifndef GUEMUD_ENTITY_H_
#define GUEMUD_ENTITY_H_

#include <string>
#include <vector>

namespace guemud {
  typedef unsigned int EntityId;

  class Entity {
    public:
      Entity();

      std::string  GetDescription();
      EntityId     GetId();
      std::string  GetName();
      void         SetDescription(std::string desc);
      void         SetName(std::string name);
    protected:
      std::string description_;
      EntityId    id_;
      std::string name_;
  };
}

#endif
