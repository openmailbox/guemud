#include "look_command.h"

namespace guemud {
namespace commands {

void LookCommand::Execute(Player& enactor) {
  Entity::Reference ref        = enactor.GetLocation();
  networking::Connection* conn = enactor.GetConnection();
  Room* room                   = RoomDB.Load(ref.id);

  std::vector<Entity::Reference>::iterator itr = room->BeginContents();

  conn->GetProtocol()->SendString(*conn, room->GetName() + "\n");
  conn->GetProtocol()->SendString(*conn, room->GetDescription() + "\n");
  conn->GetProtocol()->SendString(*conn, "Players here:\n");

  while (itr != room->EndContents()) {
    Player* player = PlayerDB.Load((*itr).id);
    conn->GetProtocol()->SendString(*conn, player->GetName() + "\n");
    itr++;
  }
  }
}
}
