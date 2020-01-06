#pragma once

#include "privilege.h"

#define VALIDATABLE_BY(type, field)                                       \
  type field = INVALID_ID<type>;                                          \
  inline bool valid() const { return field != INVALID_ID<type>; }

namespace app {
  template<typename T>
  static constexpr T INVALID_ID;

  template<>
  constexpr int INVALID_ID<int> = -1;

  template<>
  constexpr const char *INVALID_ID<const char *> = "";

  template<>
  constexpr logic::privilege_level INVALID_ID<logic::privilege_level> =
    logic::privilege_level::none;
} // namespace app
