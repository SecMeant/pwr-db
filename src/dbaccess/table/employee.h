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
  };
} // namespace app::dbaccess
