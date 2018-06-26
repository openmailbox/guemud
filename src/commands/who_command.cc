#include "who_command.h"

namespace guemud {
  namespace commands {
    void WhoCommand::Execute(Player& enactor) {
      networking::Connection* conn      = enactor.GetConnection();
      std::vector<Player*>* players       = Game::GetInstance().GetPlayers();
      std::vector<Player*>::iterator itr = players->begin();

      conn->GetProtocol()->SendString(*conn, "Connected Players:\n");

      while (itr != players->end()) {
        conn->GetProtocol()->SendString(*conn, (*itr)->GetName() + "\n");
        itr++;
      }

      conn->GetProtocol()->SendString(*conn, "---\n");
    }
  }
}
