#pragma once

#include "../action.h"
#include "../command.h"
#include "../game.h"

namespace guemud {
namespace commands {

class QuitCommand : public guemud::Command {
 public:
  void Execute(Player& enactor) override;
};

}  // namespace commands
}  // namespace guemud
