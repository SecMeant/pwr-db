#pragma once

#include <string_view>

#include "dbaccess/db_connection.h"
#include "dbaccess/db_session.h"
#include "dbaccess/table/credentials.h"
#include "dbaccess/table/employee.h"
#include "privilege.h"

namespace app::logic {

  class hldb_i;

  class session_manager
  {
  public:
    bool
    authenticate(std::string_view username,
                 std::string_view password) noexcept;

    bool
    set_privilege(dbaccess::employee_t employee,
                  privilege_level priv) noexcept;

    inline auto
    privilege() const noexcept
    {
      return this->m_privilege;
    }

    inline auto
    state() const noexcept
    {
      return this->m_state;
    }

    inline const auto &
    current() const noexcept
    {
      return this->m_session;
    }

  private:
    dbaccess::credentials_t
    auth_(std::string_view username, std::string_view password) noexcept;

    dbaccess::credentials_t
    get_user_info(std::string_view username) noexcept;

    std::string
    hash(std::string_view s) noexcept;

  private:
    bool
    low_priv_auth() noexcept;

    state_t m_state;
    privilege_level m_privilege;
    dbaccess::employee_t m_session;
    hldb_i *parent;
  };

} // namespace app::logic
