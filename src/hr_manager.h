#pragma once

#include "dbaccess/table/employee.h"

namespace app::logic {
  class hldb_i;

  class hr_manager
  {
    hldb_i* parent;
  public:
    hr_manager()=default;
    hr_manager(hldb_i*);
    bool
    modify_salary(int employee_id, int new_salary) noexcept;

    bool
    promote(int employee_id, privilege_level new_priv) noexcept;

    // id is ignored
    bool
    hire(const dbaccess::employee_t &emp) noexcept;

    bool
    fire(int employee_id) noexcept;
  };

}
