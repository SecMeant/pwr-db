#pragma once

#include <string>

namespace app::dbaccess {
struct customer_t
{
  int id;
  std::string name;
  std::string surname;
  std::string email;
};

}
