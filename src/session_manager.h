#pragma once

#include "privilege.h"
#include "dbaccess/table/credentials.h"
#include "dbaccess/table/employee.h"
#include "dbaccess/db_session.h"

namespace app::logic {

  class hldb;

  class session_manager
  {
  public:
    bool
    authenticate(dbaccess::credentials_t creds) noexcept;

    bool
    set_privilege(dbaccess::employee_t employee, privilege_level priv) noexcept;

    inline auto
    privilege() const noexcept
    { return this->m_privilege; }

    inline auto
    state() const noexcept
    { return this->m_state; }

    inline const auto&
    current() const noexcept
    { return this->m_session; }

  private:
    hldb*
    parent() noexcept;

    bool
    low_priv_auth() noexcept;


    state_t m_state;
    privilege_level m_privilege;
    dbaccess::employee_t m_session;
  };

}
