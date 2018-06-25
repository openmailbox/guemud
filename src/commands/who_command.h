#ifndef GUEMUD_COMMANDS_WHO_COMMAND_H_
#define GUEMUD_COMMANDS_WHO_COMMAND_H_

#include <vector>

#include "../command.h"
#include "../game.h"

namespace guemud {
  namespace commands {
    class WhoCommand : public guemud::Command {
      public:
        void Execute(Player& enactor);
    };
  }
}

#endif