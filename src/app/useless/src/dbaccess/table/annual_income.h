#pragma once

#include "dbaccess/table/valid.h"

namespace app::dbaccess {
  struct annual_income_t
  {
    VALIDATABLE_BY(int, id);
    int year;
    int balance;

    inline static annual_income_t
    make_any()
    {
      annual_income_t ret;

      sql::set_any(ret.id);
      sql::set_any(ret.year);
      sql::set_any(ret.balance);

      return ret;
    }
  };
} // namespace app::dbaccess
