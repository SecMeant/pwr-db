#pragma once
#include "entity_manipulator.h"
#include "dbaccess/table/offer.h"


namespace app::dbaccess
{
  class data_access_manager;

  using offer_manager_i = entity_manipulator<offer_t>;

  class offer_manager : public offer_manager_i
  {
  public:
    offer_manager() =default;
    ~offer_manager() =default;

    std::vector<offer_t> get_all() noexcept override;
    std::vector<offer_t> get_like(const offer_t &entity) noexcept override;
    offer_t get(int id) noexcept override;
    void add(const offer_t &entity) noexcept override;
    void modify(const offer_t &entity) noexcept override;
    void remove(const offer_t &entity) noexcept override;

  private:
    data_access_manager*
    parent() noexcept;
    std::string
    glue_params(const offer_t &entity, std::string separator) noexcept;

  };
}
