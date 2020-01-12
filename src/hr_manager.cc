#include "hr_manager.h"
#include "hldb.h"
#include "reflect.h"
#include "dbaccess/table/valid.h"

#include <fmt/format.h>

namespace app::logic {
  hr_manager::hr_manager(hldb_i* p)
  {
    this->parent = p;
  }
  bool
  hr_manager::modify_salary(int employee_id, int new_salary) noexcept
  {
    constexpr auto query_template = "UPDATE employees "
                                    "SET salary = {} "
                                    "WHERE id = {}";

    return this->parent->raw_query(fmt::format(query_template, new_salary, employee_id));
  }

  bool
  hr_manager::promote(int employee_id, privilege_level new_priv) noexcept
  {
    constexpr auto query_template = "UPDATE credentials "
                                    "SET privilege = {} "
                                    "WHERE employeeid = {}";

    return this->parent->raw_query(fmt::format(query_template, static_cast<int>(new_priv), employee_id));
  }

  bool
  hr_manager::hire(const dbaccess::employee_t &emp) noexcept
  {
    return this->parent->add_employee(emp);
  }

  bool
  hr_manager::fire(int employee_id) noexcept
  {
    return this->parent->remove_employee(employee_id);
  }
}
