#pragma once

#include "../command.h"
#include "../database.h"
#include "../room.h"

namespace guemud {
namespace commands {

class LookCommand : public guemud::Command {
 public:
  void Execute(Player& enactor) override;
};

}  // namespace commands
}  // namespace guemud
