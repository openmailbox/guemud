#include "sqlite.h"

namespace guemud {
namespace database {

  const std::string Sqlite::kDatabaseFile = "data/guemud.sqlite3";

  int Sqlite::CallbackSelectRows(void* result, int column_count, char** values,
                                 char** columns) {
    DatabaseRow row;

    for (int i = 0; i < column_count; i++) {
      row.insert(std::make_pair(columns[i], values[i]));
    }

    ((DatabaseResult*)result)->push_back(row);

    return 0;
  }

  DatabaseResult Sqlite::Execute(std::string query) {
    DatabaseResult result;
    char* error_message = 0;

    int err = sqlite3_exec(db_, query.data(), CallbackSelectRows, &result, &error_message);

    if (err != SQLITE_OK) {
      SystemLog.Log("SQL error: " + (std::string)error_message);
      sqlite3_free(error_message);
    }

    return result;
  }

  void Sqlite::Initialize() {
    int err = sqlite3_open(kDatabaseFile.data(), &db_);

    if (err != SQLITE_OK) {
      std::string msg = sqlite3_errmsg(db_);
      SystemLog.Log("Unable to open database: " + msg);
      sqlite3_close(db_);
      throw msg;
    }
  }


}
}