#pragma once

#include "dbaccess/table/valid.h"
#include <string>

namespace app::dbaccess {
  struct customer_t
  {
    VALIDATABLE_BY(int, id)
    std::string name;
    std::string surname;
    std::string email;
    std::string pesel;
  };

} // namespace app::dbaccess
