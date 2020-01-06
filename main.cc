#include "dbaccess/db_connection.h"
#include "dbaccess/db_defaults.h"
#include "dbaccess/data_access_manager.h"

#include <fmt/format.h>

using namespace std;
using namespace app::dbaccess;
using namespace app::dbaccess::defaults;

int
main()
{
  db_connection c(
    DB_HOSTNAME, DB_DATABASE, DB_PORT_NO, { DB_USERNAME_HIPRIO, DB_PASSWORD_HIPRIO });
  if (!c)
    fmt::print("Failed to open db con\n");
  else
    fmt::print("Db connected");
}
