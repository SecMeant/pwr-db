#pragma once

#include "../date.h"
#include "dbaccess/table/valid.h"

#include <chrono>
#include <string>

namespace app::dbaccess {

  struct employee_t
  {
    VALIDATABLE_BY(int, id)
    std::string name;
    std::string surname;
    date_t hire_date;
    int salary;
    std::string email;
    std::string phone_number;

    inline static employee_t
    make_any()
    {
      employee_t ret;

      sql::set_any(ret.id);
      sql::set_any(ret.name);
      sql::set_any(ret.surname);
      sql::set_any(ret.hire_date);
      sql::set_any(ret.salary);
      sql::set_any(ret.email);
      sql::set_any(ret.phone_number);

      return ret;
    }
  };
} // namespace app::dbaccess
