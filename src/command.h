#ifndef GUEMUD_COMMAND_H_
#define GUEMUD_COMMAND_H_

#include "player.h"

namespace guemud {
  class Command {
    public:
      virtual void Execute(Player& enactor) = 0;
  };
}

#endif
