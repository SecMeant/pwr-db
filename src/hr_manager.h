#pragma once

#include "dbaccess/table/employee.h"

namespace app::logic {
  class hldb;

  class hr_manager
  {
  public:
    bool
    modify_salary(int employee_id, int new_salary) noexcept;

    bool
    promote(int employee_id, privilege_level new_priv) noexcept;

    // id is ignored
    bool
    hire(const dbaccess::employee_t &emp) noexcept;

    bool
    fire(int employee_id) noexcept;

  private:
    hldb*
    parent() noexcept;
  };

}
