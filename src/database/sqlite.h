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

class Sqlite {
 public:
  void           Initialize();
  DatabaseResult Execute(std::string query);

 private:
  static const std::string kDatabaseFile; // TODO: Replace with configuration

  static int CallbackSelectRows(void* result, int column_count, char** values,
                                char** columns);

  sqlite3* db_;
};

}
}
