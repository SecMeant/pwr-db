#pragma once

#include <memory>
#include <mysql/mysql.h>

namespace app::dbaccess {

  struct mysql_res_deleter
  {
    void
    operator()(MYSQL_RES *res) const noexcept
    {
      mysql_free_result(res);
    }
  };

  struct mysql_conn_deleter
  {
    void
    operator()(MYSQL *conn) const noexcept
    {
      mysql_close(conn);
    }
  };

  using mysql_res_t = std::unique_ptr<MYSQL_RES, mysql_res_deleter>;
  using mysql_conn_t = std::unique_ptr<MYSQL, mysql_conn_deleter>;

} // namespace app::dbaccess
