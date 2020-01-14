#pragma once

#include "dbaccess/table/valid.h"
#include <string>

namespace app::dbaccess {
  struct category_t
  {
    static constexpr size_t field_count = 2;

    VALIDATABLE_BY(int, id);
    std::string name;

    inline static category_t
    make_any()
    {
      category_t ret;

      sql::any(ret.id);
      sql::any(ret.name);

      return ret;
    }
  };
} // namespace app::dbaccess
