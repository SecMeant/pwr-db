#pragma once
#include "entity_manipulator.h"
#include "dbaccess/table/offer.h"


namespace app::dbaccess
{
  class data_access_manager;

  using offer_manipulator_i = entity_manipulator<offer_t>;

  class offer_manipulator : public offer_manipulator_i
  {
  public:
    offer_manipulator() =default;
    ~offer_manipulator() =default;

    std::vector<offer_t> get_all() noexcept override;
    std::vector<offer_t> get_like(const offer_t &entity) noexcept override;
    offer_t get(int id) noexcept override;
    bool add(const offer_t &entity) noexcept override;
    bool modify(const offer_t &entity) noexcept override;
    bool remove(int id) noexcept override;

  private:
    data_access_manager*
    parent() noexcept;
    std::string
    glue_params(const offer_t &entity, std::string separator) noexcept;

  };
}
