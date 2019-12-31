#pragma once

#include <vector>

namespace app::dbaccess {
  template <typename T>
  class entity_manipulator
  {
  public:
    virtual std::vector<T> get_all() noexcept = 0;
    virtual T get_like(const T &entity) noexcept = 0;
    virtual T get(int id) noexcept = 0;
    virtual void add(const T &entity) noexcept = 0;
    virtual void modify(const T &entity) noexcept = 0;
    virtual void remove(const T &entity) noexcept = 0;
  };
}
