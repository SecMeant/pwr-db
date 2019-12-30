#include "db_connection.h"
#include "db_defaults.h"

#include <fmt/format.h>

namespace app::db_access {

  mysql_res_t
  db_connection::query(const std::string &query_string) noexcept
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
  db_connection::authenticate_user(const std::string &username,
                                   const std::string &password) noexcept
  {
    return false;
  }

  void
  db_connection::close() noexcept
  {
    if (!this->connected)
      return;

    mysql_close(this->connection.get());
    this->connection = nullptr;
    this->connected = false;
  }

  bool
  db_connection::low_prio_auth() noexcept
  {
    this->connection = mysql_conn_t(mysql_init(NULL));
    this->connected = mysql_real_connect(this->connection.get(),
                                         this->hostname.c_str(),
                                         defaults::DB_USERNAME,
                                         defaults::DB_PASSWORD,
                                         this->database.c_str(),
                                         this->port,
                                         nullptr,
                                         0);
    return this->connected;
  }

  static std::string
  get_users_hash(db_connection *conn, const std::string &username)
  {
    constexpr auto query_template =
      "SELECT pass_hash from credentials where login = \"{}\"";

    auto res = conn->query(fmt::format(query_template, username));

    if (!res || mysql_num_rows(res.get()) != 1)
      return "";

    return mysql_fetch_row(res.get())[0];
  }

  bool
  db_connection::check_credentials(const db_session &creds) noexcept
  {
    auto stored_hash = get_users_hash(this, creds.username);

    if (stored_hash.empty())
      return false;

    if (stored_hash != creds.get_password_hash())
      return false;

    return true;
  }

} // namespace app::db_access
