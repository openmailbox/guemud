#pragma once

#include <string>

#include "../action.h"
#include "../command.h"
#include "../game.h"

namespace guemud {
namespace commands {

class ChatCommand : public guemud::Command {
 public:
  std::string GetMessage();
  void Execute(Player& enactor) override;
  void SetMessage(std::string message);

 private:
  std::string message_;
};

}  // namespace commands
}  // namespace guemud
