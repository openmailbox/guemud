#include "logon.h"
#include "networking/connection.h"

namespace guemud {
  Logon::Logon(networking::Connection* conn) : networking::ConnectionHandler(conn) {}

  void Logon::Enter() {
    connection_->GetProtocol()->SendString(*connection_, "Enter your username: ");
  }

  void Logon::Handle(std::string data) {
    networking::Connection* conn = connection_;
    Player* player               = (Player*)PlayerDB.Create();
    Room* room                   = (Room*)RoomDB.First();

    player->SetConnection(*conn);
    player->SetName(data);
    player->SetLocation(*room);

    room->AddEntity(*player);

    conn->GetProtocol()->SendString(*connection_, "Welcome, " + player->GetName() + ".\n");
    conn->RemoveHandler();
    conn->AddHandler(new Chat(conn, player));
  }
}
