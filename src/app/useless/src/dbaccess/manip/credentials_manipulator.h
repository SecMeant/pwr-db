#pragma once
#include "dbaccess/table/credentials.h"
#include "entity_manipulator.h"

#include <string_view>

namespace app::dbaccess {
  class data_access_manager;

  using credentials_manipulator_i = entity_manipulator<credentials_t>;

  class credentials_manipulator : public credentials_manipulator_i
  {
  public:
    credentials_manipulator() = default;
    ~credentials_manipulator() = default;

    std::vector<credentials_t>
    get_all() const noexcept override;
    std::vector<credentials_t>
    get_like(const credentials_t &entity) const noexcept override;
    credentials_t
    get(int id) const noexcept override;
    bool
    add(const credentials_t &entity) const noexcept override;
    bool
    modify(const credentials_t &entity) const noexcept override;
    bool
    remove(int id) const noexcept override;

    data_access_manager *
    parent() const noexcept;

  private:
    std::string
    glue_params(const credentials_t &entity, std::string_view separator, std::string_view eq = "LIKE") const
      noexcept;
  };
} // namespace app::dbaccess
