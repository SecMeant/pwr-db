#pragma once

#include "mysql_types.h"

#include <string>
#include <string_view>

namespace app::dbaccess {
  class db_connection_i
  {
  public:
    virtual mysql_res_t
    query_res(const std::string &query_string) noexcept = 0;

    virtual bool
    query(const std::string &query_string) noexcept = 0;

    virtual bool
    authenticate(std::string_view username, std::string_view password) noexcept = 0;

    virtual void
    close() noexcept = 0;
    virtual ~db_connection_i()=default;
  };
} // namespace app::dbaccess
