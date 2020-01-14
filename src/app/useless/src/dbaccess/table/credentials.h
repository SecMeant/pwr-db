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

    inline static credentials_t
    make_any()
    {
      credentials_t ret;

      sql::set_any(ret.id);
      sql::set_any(ret.employeeid);
      sql::set_any(ret.login);
      sql::set_any(ret.pass_hash);
      sql::set_any(ret.privilege);

      return ret;
    }
  };
} // namespace app::dbaccess
