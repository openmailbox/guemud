#include "sqlite3.h"

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../logger.h"

namespace guemud {
namespace database {

typedef std::map<std::string, std::string> DatabaseRow;
typedef std::vector<DatabaseRow>           DatabaseResult;

class SqliteCursor {
 public:
   SqliteCursor(sqlite3_stmt*);
   ~SqliteCursor();

   DatabaseRow GetCurrentRow();
   bool        IsFinished();
   void        Next();
 private:

   bool          is_finished_;
   sqlite3_stmt* statement_;
};

class SqliteAdapter {
 public:
  void           Initialize();
  DatabaseResult Execute(std::string query);
  SqliteCursor   Prepare(std::string query);
  void           Shutdown();

 private:
  static const std::string kDatabaseFile; // TODO: Replace with configuration

  static int CallbackSelectRows(void* result, int column_count, char** values,
                                char** columns);

  sqlite3* db_;
};


}
}
