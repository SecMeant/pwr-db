#include "hr_manager.h"
#include "hldb.h"
#include "reflect.h"
#include "dbaccess/table/valid.h"

#include <fmt/format.h>

namespace app::logic {
  bool
  hr_manager::modify_salary(int employee_id, int new_salary) noexcept
  {
    auto& dbconn = this->parent()->m_dbconn;

    constexpr auto query_template = "UPDATE employees "
                                    "SET salary = {} "
                                    "WHERE id = {}";

    return dbconn.query(fmt::format(query_template, new_salary, employee_id));
  }

  bool
  hr_manager::promote(int employee_id, privilege_level new_priv) noexcept
  {
    auto& dbconn = this->parent()->m_dbconn;

    constexpr auto query_template = "UPDATE credentials "
                                    "SET privilege = {} "
                                    "WHERE employeeid = {}";

    return dbconn.query(fmt::format(query_template, static_cast<int>(new_priv), employee_id));
  }

  bool
  hr_manager::hire(const dbaccess::employee_t &emp) noexcept
  {
    auto& parent = *this->parent();
    return parent.add_employee(emp);
  }

  bool
  hr_manager::fire(int employee_id) noexcept
  {
    auto& parent = *this->parent();
    return parent.remove_employee(employee_id);
  }

  hldb*
  hr_manager::parent() noexcept
  {
    return container_of(this, logic::hldb, m_hr);
  }
}
