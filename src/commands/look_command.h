#pragma once

#include "../action.h"
#include "../command.h"
#include "../game.h"
#include "../room.h"

namespace guemud {
namespace commands {

class LookCommand : public guemud::Command {
 public:
  void Execute(Player& enactor) override;
};

}  // namespace commands
}  // namespace guemud
