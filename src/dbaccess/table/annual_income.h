#pragma once

#include "dbaccess/table/valid.h"

namespace app::dbaccess {
  struct annual_income_t
  {
    VALIDATABLE_BY(int, id);
    int year;
    int balance;
  };
}
