#include "logon.h"
#include "networking/connection.h"

namespace guemud {
  Logon::Logon(networking::Connection* conn) : networking::ConnectionHandler(conn) {}

  void Logon::Enter() {
    connection_->GetProtocol()->SendString(*connection_, "Enter your username: ");
  }

  void Logon::Handle(std::string data) {
    networking::Connection* conn = connection_;
    Player* player = Game::GetInstance().NewPlayer(conn, data);

    conn->GetProtocol()->SendString(*connection_, "Welcome, " + player->GetName() + ".\n");
    conn->RemoveHandler();
    conn->AddHandler(new Chat(conn, player));
  }
}
