#include "look_command.h"

namespace guemud {
namespace commands {

void LookCommand::Execute(Player& enactor) {
  Entity::Reference ref        = enactor.GetLocation();
  networking::Connection* conn = enactor.GetConnection();

  conn->GetProtocol()->SendString(*conn, "Room");
}

}
}
