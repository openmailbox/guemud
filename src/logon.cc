#include "logon.h"
#include "networking/connection.h"

namespace guemud {
  Logon::Logon(networking::Connection& conn) : networking::ConnectionHandler(conn) {}

  void Logon::Enter() {
    connection_->GetProtocol()->SendString(*connection_, "Enter your username: ");
  }

  void Logon::Handle(std::string data) {
    connection_->name = data;
    connection_->GetProtocol()->SendString(*connection_, "Welcome, " + data + ".\n");
    connection_->RemoveHandler();
    connection_->AddHandler(new Chat(*connection_));
  }
}
