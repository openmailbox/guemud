#include "chat.h"
#include "networking/connection.h"

namespace guemud {
  Chat::Chat(networking::Connection* conn) : networking::ConnectionHandler(conn) {}

  void Chat::Enter() {
    ShowPrompt();
  }

  void Chat::Handle(std::string data) {
    connection_->GetProtocol()->SendString(*connection_, "You say, \"" + data + "\"\n");
    ShowPrompt();
  }

  void Chat::ShowPrompt() {
    connection_->GetProtocol()->SendString(*connection_, "> ");
  }
}
