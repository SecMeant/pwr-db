#pragma once

#include "mysql_types.h"

#include <string>

namespace app::db_access {
  class db_connection_i
  {
  public:
    virtual mysql_res_t
    query(const std::string &query_string) noexcept = 0;

    virtual bool
    authenticate_user(const std::string &username,
                      const std::string &password) noexcept = 0;

    virtual void
    close() noexcept = 0;
  };
} // namespace app::db_access
