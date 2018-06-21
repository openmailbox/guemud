#include "chat.h"
#include "connection.h"

guemud::Chat::Chat(Connection& conn) : ConnectionHandler(conn) {}

void guemud::Chat::Enter() {
  ShowPrompt();
}

void guemud::Chat::Handle(std::string data) {
  connection_->GetProtocol()->SendString(*connection_, "You say, \"" + data + "\"\n");
  ShowPrompt();
}

void guemud::Chat::ShowPrompt() {
  connection_->GetProtocol()->SendString(*connection_, "> ");
}
