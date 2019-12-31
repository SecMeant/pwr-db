#include "dbaccess/db_connection.h"
#include "dbaccess/db_defaults.h"

#include <fmt/format.h>

using namespace std;
using namespace app::dbaccess;
using namespace app::dbaccess::defaults;

int
main()
{
  db_connection c(
    DB_HOSTNAME, DB_DATABASE, DB_PORT_NO, { DB_USERNAME, DB_PASSWORD });

  if (!c)
    fmt::print("Failed to open db con\n");
}
