#pragma once

#include "privilege.h"
#include "dbaccess/credentials.h"
#include "dbaccess/employee.h"
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

  private:
    hldb*
    parent() noexcept;

    bool
    low_priv_auth() noexcept;


    state_t m_state;
    privilege_level m_privilege;
  };

}
