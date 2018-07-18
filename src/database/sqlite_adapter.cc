#include "sqlite_adapter.h"

namespace guemud {
namespace database {

SqliteCursor::SqliteCursor(sqlite3_stmt* stmt) : statement_(stmt) {
  is_finished_ = false;
  Next() ; // advance to the first row
};

SqliteCursor::~SqliteCursor() {
  sqlite3_finalize(statement_);
}

DatabaseRow SqliteCursor::GetCurrentRow() {
  DatabaseRow row;

  for (int i = 0; i < sqlite3_data_count(statement_); i++) {
    int type                = sqlite3_column_type(statement_, i);
    std::string column_name = sqlite3_column_name(statement_, i);

    // The only types we care about are strings and integers. Return everything as a string for now
    if (type == SQLITE_INTEGER) {
      int value = sqlite3_column_int(statement_, i);
      row.insert(std::make_pair(column_name, std::to_string(value)));
    } else if (type == SQLITE_TEXT) {
      std::string value((const char*)sqlite3_column_text(statement_, i));
      row.insert(std::make_pair(column_name, value));
    } else {
      SystemLog.Log("SQL Warning: Unable to parse data type " +
                    std::to_string(type));
    }
  }

  return row;
}

bool SqliteCursor::IsFinished() {
  return is_finished_;
}

void SqliteCursor::Next() {
  int err = sqlite3_step(statement_);

  if (err == SQLITE_DONE) {
    is_finished_ = true;
  } else if (err != SQLITE_ROW) {
    SystemLog.Log("SQL error: " + std::to_string(err));
    throw err;
  }
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

SqliteCursor SqliteAdapter::Prepare(std::string query) {
  sqlite3_stmt* statement;

  int err = sqlite3_prepare_v2(db_, query.data(), query.length(), &statement, NULL);

  if (err != SQLITE_OK) {
    SystemLog.Log("SQL error: " + std::to_string(err));
    throw err;
  }

  return SqliteCursor(statement);
}

void SqliteAdapter::Shutdown() {
  sqlite3_close_v2(db_);
}

}
}
