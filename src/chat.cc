#include "chat.h"
#include "networking/connection.h"

namespace guemud {
  Chat::Chat(networking::Connection* conn, Player* player) :
    networking::ConnectionHandler(conn), player_(player) {}

  void Chat::Enter() {
    ShowPrompt();
  }

  void Chat::Handle(std::string data) {
    if (data.compare("/who") == 0) {
      commands::WhoCommand cmd;
      cmd.Execute(*player_);
    } else if (data.compare("look") == 0) {
      commands::LookCommand cmd;
      cmd.Execute(*player_);
    } else {
      Game::GetInstance().Announce(player_->GetName() + " says, \"" + data + "\"\n");
    }
    // TODO: Prompt shows up before timed actions
    ShowPrompt();
  }

  void Chat::ShowPrompt() {
    connection_->GetProtocol()->SendString(*connection_, "\n> ");
  }
}
