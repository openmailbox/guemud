#include "chat.h"
#include "networking/connection.h"

namespace guemud {
  Chat::Chat(networking::Connection* conn, Player player) : 
    networking::ConnectionHandler(conn), player_(player) {}

  void Chat::Enter() {
    ShowPrompt();
  }

  void Chat::Handle(std::string data) {
    Game::GetInstance().Announce(player_.GetName() + " says, \"" + data + "\"\n");
    ShowPrompt();
  }

  void Chat::ShowPrompt() {
    connection_->GetProtocol()->SendString(*connection_, "> ");
  }
}
