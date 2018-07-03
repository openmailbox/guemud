#include "chat_command.h"

namespace guemud {
namespace commands {

std::string guemud::commands::ChatCommand::GetMessage() { return message_; }

void guemud::commands::ChatCommand::Execute(Player& enactor) {
  Entity::Reference ref;
  ref.id   = enactor.GetId();
  ref.type = typeid(enactor).name();

  Action action;
  action.action_type = "chat";
  action.entities.push_back(ref);

  Game::GetInstance().AddAction(action);
}

void guemud::commands::ChatCommand::SetMessage(std::string message) { message_ = message; }

}
}