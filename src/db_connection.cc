#include "db_connection.h"

namespace app::db_access {

  mysql_res_t db_connection::query(std::string query_string) noexcept
  {
    return make_sql_res(nullptr);
  }

  bool db_connection::authenticate_user(std::string username, std::string password) noexcept
  {
    return false;
  }

  void db_connection::shutdown() noexcept
  {
    mysql_close(this->connection.get());
  }

}
