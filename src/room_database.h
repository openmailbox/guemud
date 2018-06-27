#ifndef GUEMUD_ROOM_DATABASE_H_
#define GUEMUD_ROOM_DATABASE_H_

#include "database.h"
#include "room.h"

namespace guemud {

class RoomDatabase : public Database<Room> {
};

extern RoomDatabase RoomDB;

}

#endif
