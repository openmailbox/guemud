#include "sqlite_adapter.h"

namespace guemud {
namespace database {

SqliteCursor::SqliteCursor(sqlite3_stmt* stmt) : statement_(stmt) {};

SqliteCursor::~SqliteCursor() {
  sqlite3_finalize(statement_);
}

SqliteCursor SqliteAdapter::Prepare(std::string query) {
  sqlite3_stmt* statement;

  int err = sqlite3_prepare_v2(db_, query.data(), query.length(), &statement, NULL);

  if (err != SQLITE_OK) {
    SystemLog.Log("SQL error: " + std::to_string(err));
    throw err;
  }

  return SqliteCursor(statement);
}

DatabaseRow SqliteCursor::Next() {
  int err = sqlite3_step(statement_);

  if (err != SQLITE_OK) {
    SystemLog.Log("SQL error: " + std::to_string(err));
    throw err;
  }

  return DatabaseRow();
}

const std::string SqliteAdapter::kDatabaseFile = "data/guemud.sqlite3";

int SqliteAdapter::CallbackSelectRows(void* result, int column_count, char** values,
    char** columns) {
  DatabaseRow row;

  for (int i = 0; i < column_count; i++) {
    row.insert(std::make_pair(columns[i], values[i]));
  }

  ((DatabaseResult*)result)->push_back(row);

  return 0;
}

DatabaseResult SqliteAdapter::Execute(std::string query) {
  DatabaseResult result;
  char* error_message = 0;

  int err = sqlite3_exec(db_, query.data(), CallbackSelectRows, &result, &error_message);

  if (err != SQLITE_OK) {
    SystemLog.Log("SQL error: " + (std::string)error_message);
    sqlite3_free(error_message);
  }

  return result;
}

void SqliteAdapter::Initialize() {
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
