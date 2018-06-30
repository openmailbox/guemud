#pragma once

#include <string>
#include <vector>

#include "entity.h"

namespace guemud {

struct Action {
  std::string                    action_type;
  std::string                    data;
  std::vector<Entity::Reference> entities;
};

}
