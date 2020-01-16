#pragma once
#include "dbaccess/table/offer.h"
#include "entity_manipulator.h"

#include <string_view>

namespace app::dbaccess {
  class data_access_manager;

  using offer_manipulator_i = entity_manipulator<offer_t>;

  class offer_manipulator : public offer_manipulator_i
  {
  public:
    offer_manipulator() = default;
    ~offer_manipulator() = default;

    std::vector<offer_t>
    get_all() const noexcept override;
    std::vector<offer_t>
    get_like(const offer_t &entity) const noexcept override;
    offer_t
    get(int id) const noexcept override;
    bool
    add(const offer_t &entity) const noexcept override;
    bool
    modify(const offer_t &entity) const noexcept override;
    bool
    remove(int id) const noexcept override;

    data_access_manager *
    parent() const noexcept;

  private:
    std::string
    glue_params(const offer_t &entity, std::string_view separator, std::string_view eq = "LIKE") const
      noexcept;
  };
} // namespace app::dbaccess
