#pragma once

#include "../command.h"

namespace guemud {
namespace  commands {

class LookCommand : public guemud::Command {
 public:
   void Execute(Player& enactor) override;
};

}
}
