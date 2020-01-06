#pragma once

#include "dbaccess/table/valid.h"
#include <string>

namespace app::dbaccess {
struct category_t
{
  VALIDATABLE_BY(int, id);
  std::string name;
};
}
