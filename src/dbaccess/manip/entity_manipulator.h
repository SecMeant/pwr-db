#pragma once

#include <limits>
#include <vector>

constexpr const char *UNWANTED_STR_PARAM = "";
constexpr int UNWANTED_DECIMAL_PARAM = -1;
constexpr const char *INVALID_DATE = "01.01.70";

namespace app::dbaccess {
  template<typename T>
  class entity_manipulator
  {
  public:
    virtual std::vector<T>
    get_all() const noexcept = 0;
    virtual std::vector<T>
    get_like(const T &entity) const noexcept = 0;
    virtual T
    get(int id) const noexcept = 0;
    virtual bool
    add(const T &entity) const noexcept = 0;
    virtual bool
    modify(const T &entity) const noexcept = 0;
    virtual bool
    remove(int id) const noexcept = 0;
    virtual ~entity_manipulator() = default;
  };
} // namespace app::dbaccess
