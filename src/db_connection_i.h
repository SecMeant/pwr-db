#pragma once

#include <memory>
#include <string>

#include <mysql/mysql.h>

namespace app::db_access {
  using mysql_res_t =
    std::unique_ptr<MYSQL_RES, decltype(&mysql_free_result)>;

  inline mysql_res_t make_sql_res(MYSQL_RES *res_raw)
  { return {res_raw, &mysql_free_result}; }

  class db_connection_i
  {
  public:
    virtual mysql_res_t
    query(std::string query_string) noexcept = 0;

    virtual bool
    authenticate_user(std::string username,
                      std::string password) noexcept = 0;
    virtual void
    shutdown() noexcept = 0;
  };
} // namespace app::db_access
