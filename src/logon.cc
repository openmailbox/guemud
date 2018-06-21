#include "logon.h"
#include "connection.h"

guemud::Logon::Logon(Connection& conn) : ConnectionHandler(conn) {}

void guemud::Logon::Enter() {
  connection_->GetProtocol()->SendString(*connection_, "Enter your username: ");
}

void guemud::Logon::Handle(std::string data) {
  connection_->name = data;
  connection_->GetProtocol()->SendString(*connection_, "Welcome, " + data + ".\n");
  connection_->RemoveHandler();
  connection_->AddHandler(new Chat(*connection_));
}


