#pragma once

namespace app::logic {
  enum class state_t
  {
    logedin,
    logedout
  };

  enum class privilege_level : int
  {
    none = -1,
    low = 0,
    mid = 1,
    high = 2
  };
} // namespace app::logic
