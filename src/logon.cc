#include "logon.h"
#include "connection.h"

guemud::Logon::Logon(Connection& conn) : ConnectionHandler(conn) {}

void guemud::Logon::Enter() {
  connection_->GetProtocol()->SendString(*connection_, "Enter your username: ");
}
