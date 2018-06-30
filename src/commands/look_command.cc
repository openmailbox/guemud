#include "look_command.h"

namespace guemud {
namespace commands {

void LookCommand::Execute(Player& enactor) {
  Entity::Reference ref        = enactor.GetLocation();
  networking::Connection* conn = enactor.GetConnection();
  Room* room                   = RoomDB.Load(ref.id);

  conn->GetProtocol()->SendString(*conn, room->GetName() + "\n");
  conn->GetProtocol()->SendString(*conn, room->GetDescription() + "\n");
}

}
}
