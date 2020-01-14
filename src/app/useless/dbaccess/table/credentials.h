#pragma once

#include "dbaccess/table/valid.h"
#include "privilege.h"

#include <string>

namespace app::dbaccess {
  struct credentials_t
  {
    int id;
    int employeeid;
    std::string login;
    std::string pass_hash;
    VALIDATABLE_BY(logic::privilege_level, privilege)
  };
} // namespace app::dbaccess
