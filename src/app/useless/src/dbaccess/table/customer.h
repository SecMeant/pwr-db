#pragma once

#include "dbaccess/table/valid.h"
#include <string>

namespace app::dbaccess {
  struct customer_t
  {
    static constexpr size_t field_count = 5;

    VALIDATABLE_BY(int, id)
    std::string name;
    std::string surname;
    std::string email;
    std::string pesel;

    inline static customer_t make_any()
    {
      customer_t ret;

      sql::set_any(ret.id);
      sql::set_any(ret.id);
      sql::set_any(ret.name);
      sql::set_any(ret.surname);
      sql::set_any(ret.email);
      sql::set_any(ret.pesel);

      return ret;
    }
  };

} // namespace app::dbaccess
