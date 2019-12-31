#pragma once

#include "../privilege.h"

#include <string>

namespace app::dbaccess {
struct credentials_t
{
  int id;
  std::string login;
  std::string pass_hash;
  logic::privilege_level privilege;

  credentials_t()
  : privilege(logic::privilege_level::none) {}

  inline bool
  valid() const noexcept
  { return this->privilege != logic::privilege_level::none; }
};
}
