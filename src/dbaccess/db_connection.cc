#include "db_connection.h"
#include "db_defaults.h"

#include <fmt/format.h>

namespace app::dbaccess {

  mysql_res_t
  db_connection::query_res(const std::string &query_string) noexcept
  {
    auto res = mysql_query(this->connection.get(), query_string.c_str());

    if (res)
      return nullptr;

    // FIXME Huge fetches from database can be buffered and therefore
    // result in better performance. If that's the case mysql_use_result
    // should be used, which returns unbuffered result. However some
    // functions might require buffered fetch to happen, because this
    // allows to call mysql_num_rows.
    return mysql_res_t(mysql_store_result(this->connection.get()));
  }

  bool
  db_connection::query(const std::string &query_string) noexcept
  {
    return !mysql_query(this->connection.get(), query_string.c_str());
  }

  bool
  db_connection::authenticate(const std::string &username,
                              const std::string &password) noexcept
  {
    this->close();

    this->connection = mysql_conn_t(mysql_init(NULL));
    this->connected = mysql_real_connect(this->connection.get(),
                                         this->hostname.c_str(),
                                         username.c_str(),
                                         password.c_str(),
                                         this->database.c_str(),
                                         this->port,
                                         nullptr,
                                         0);
    return this->connected;
  }

  void
  db_connection::close() noexcept
  {
    if (!this->connected)
      return;

    this->connection = nullptr;
    this->connected = false;
  }

} // namespace app::dbaccess
