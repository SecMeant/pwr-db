#pragma once
#include "dbaccess/table/tour.h"
#include "entity_manipulator.h"

#include <string_view>

namespace app::dbaccess {
  class data_access_manager;

  using tour_manipulator_i = entity_manipulator<tour_t>;
  class tour_manipulator : public tour_manipulator_i
  {
  public:
    tour_manipulator() = default;
    ~tour_manipulator() = default;

    std::vector<tour_t>
    get_all() const noexcept override;
    std::vector<tour_t>
    get_like(const tour_t &entity) const noexcept override;
    tour_t
    get(int id) const noexcept override;
    bool
    add(const tour_t &entity) const noexcept override;
    bool
    modify(const tour_t &entity) const noexcept override;
    bool
    remove(int id) const noexcept override;

    data_access_manager *
    parent() const noexcept;

  private:
    std::string
    glue_params(const tour_t &entity, std::string_view separator, std::string_view eq = "LIKE") const
      noexcept;
  };
} // namespace app::dbaccess
