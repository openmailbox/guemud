#include "who_command.h"

namespace guemud {
  namespace commands {
    void WhoCommand::Execute(Player& enactor) {
      networking::Connection* conn       = enactor.GetConnection();
      std::vector<Player*>::iterator itr = database::PlayerDB.Begin();

      conn->GetProtocol()->SendString(*conn, "Connected Players:\n");

      while (itr != database::PlayerDB.End()) {
        conn->GetProtocol()->SendString(*conn, (*itr)->GetName() + "\n");
        itr++;
      }

      conn->GetProtocol()->SendString(*conn, "---\n");
    }
  }
}
