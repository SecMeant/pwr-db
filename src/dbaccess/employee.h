#pragma once

#include "date.h"

#include <chrono>
#include <string>

namespace app::dbaccess {

struct employee_t
{
  int id;
  std::string name;
  std::string surname;
  date_t hire_date;
  int salary;
  std::string email;
  std::string phone_number;
};
}
