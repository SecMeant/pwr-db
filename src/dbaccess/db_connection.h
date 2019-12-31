#pragma once

#include "mysql_types.h"
#include "db_connection_i.h"
#include "db_session.h"

#include <mysql/mysql.h>

#include <memory>
#include <string>

namespace app::dbaccess {

  class db_connection final : public db_connection_i
  {
  public:
    using port_t = unsigned int;

    db_connection() = default;

    db_connection(std::string hostname,
                  std::string database,
                  port_t port,
                  db_session session) noexcept
      : hostname(std::move(hostname))
      , database(std::move(database))
      , port(port)
      , session(std::move(session))
      , connection(mysql_init(NULL))
    {
      this->connected = mysql_real_connect(this->connection.get(),
                                           this->hostname.c_str(),
                                           this->session.username.c_str(),
                                           this->session.password.c_str(),
                                           this->database.c_str(),
                                           this->port,
                                           nullptr,
                                           0);
    }

    operator bool() const noexcept { return this->connected; }

    mysql_res_t
    query_res(const std::string &query_string) noexcept override;

    bool
    query(const std::string &query_string) noexcept override;

    bool
    authenticate(const std::string &username,
                 const std::string &password) noexcept override;

    void
    close() noexcept override;

  private:
    std::string hostname;
    std::string database;
    port_t port;
    db_session session;
    mysql_conn_t connection;
    bool connected = false;
  };
} // namespace app::dbaccess
