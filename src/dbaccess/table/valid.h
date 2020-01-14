#pragma once
#pragma once
#include "../date.h"
#include "privilege.h"
#include <string>

namespace app::dbaccess {
  enum class tour_state : int
  {
    UNFINSHED = 0,
    FINISHED = 1,
    RESIGNED = 2,
    INVALID = -1,
    ANY = -2
  };
}

namespace app {

  template<typename T>
  inline T INVALID;

  template<>
  inline int INVALID<int> = -1;

  template<>
  inline logic::privilege_level INVALID<logic::privilege_level> =
    logic::privilege_level::none;

  template<>
  inline std::string INVALID<std::string> = "";

  template<>
  inline dbaccess::date_t INVALID<dbaccess::date_t> =
    dbaccess::str2epoch("01.01.70");

  template<>
  inline dbaccess::tour_state INVALID<dbaccess::tour_state> =
    dbaccess::tour_state::INVALID;

  template<typename T>
  inline T ANY;

  template<>
  inline int ANY<int> = -2;

  template<>
  inline std::string ANY<std::string> = "@";

  template<>
  inline dbaccess::date_t ANY<dbaccess::date_t> =
    dbaccess::str2epoch("02.01.70");

  template<>
  inline dbaccess::tour_state ANY<dbaccess::tour_state> =
    dbaccess::tour_state::ANY;

} // namespace app

#define VALIDATABLE_BY(type, field)                                       \
  type field = INVALID<type>;                                             \
  inline bool valid() const { return sql::valid(field); }

namespace app::sql {
  template<typename T>
  constexpr bool
  valid(const T &t)
  {
    return t != INVALID<T>;
  }

  template<typename T>
  constexpr void
  set_any(T &t)
  {
    t = ANY<T>;
  }

  template<typename T>
  constexpr void
  set_invalid(T &t)
  {
    t = INVALID<T>;
  }

  template<typename T>
  constexpr bool
  any(const T &t)
  {
    return t == ANY<T>;
  }
} // namespace app::sql