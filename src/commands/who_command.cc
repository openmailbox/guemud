#include "who_command.h"

namespace guemud {
  namespace commands {
    void WhoCommand::Execute(Player& enactor) {
      networking::Connection* conn      = enactor.GetConnection();
      std::vector<Player>::iterator itr = Game::GetInstance().GetPlayers().begin();

      conn->GetProtocol()->SendString(*conn, "Connected Players:\n");

      while (itr != Game::GetInstance().GetPlayers().end()) {
        conn->GetProtocol()->SendString(*conn, (*itr).GetName() + "\n");
        itr++;
      }

      conn->GetProtocol()->SendString(*conn, "---\n");
    }
  }
}
