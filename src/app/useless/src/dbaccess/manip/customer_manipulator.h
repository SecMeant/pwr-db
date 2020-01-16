#pragma once
#include "dbaccess/table/customer.h"
#include "entity_manipulator.h"

#include <string_view>

namespace app::dbaccess {
  class data_access_manager;

  using customer_manipulator_i = entity_manipulator<customer_t>;

  class customer_manipulator : public customer_manipulator_i
  {
  public:
    customer_manipulator() = default;
    ~customer_manipulator() = default;

    std::vector<customer_t>
    get_all() const noexcept override;
    std::vector<customer_t>
    get_like(const customer_t &entity) const noexcept override;
    customer_t
    get(int id) const noexcept override;
    bool
    add(const customer_t &entity) const noexcept override;
    bool
    modify(const customer_t &entity) const noexcept override;
    bool
    remove(int id) const noexcept override;

    data_access_manager *
    parent() const noexcept;

  private:
    std::string
    glue_params(const customer_t &entity, std::string_view separator, std::string_view eq = "LIKE") const
      noexcept;
  };
} // namespace app::dbaccess
