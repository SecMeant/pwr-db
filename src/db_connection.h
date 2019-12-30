#include "db_session.h"

#include <mysql/mysql.h>

#include <memory>
#include <string>

namespace app::db_access {

  class db_connection
  {
  public:
    using port_t = unsigned int;

    db_connection() = default;

    db_connection(std::string hostname,
                  std::string database,
                  port_t port,
                  db_session session)
      : hostname(std::move(hostname))
      , database(std::move(database))
      , port(port)
      , session(std::move(session))
      , connection(mysql_init(NULL), &mysql_close)
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

  private:
    std::string hostname;
    std::string database;
    port_t port;
    db_session session;
    std::unique_ptr<MYSQL, decltype(&mysql_close)> connection;
    bool connected = false;
  };
} // namespace app::db_access
