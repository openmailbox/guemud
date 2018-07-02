#include "look_command.h"

namespace guemud {
namespace commands {

void LookCommand::Execute(Player& enactor) {
  Entity::Reference ref;
  ref.id   = enactor.GetId();
  ref.type = typeid(enactor).name();

  Action action;
  action.action_type = "look";
  action.entities.push_back(ref);

  Game::GetInstance().AddAction(action);
}

}  // namespace commands
}  // namespace guemud
