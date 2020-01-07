#pragma once
#include "entity_manipulator.h"
#include "dbaccess/table/customer.h"


namespace app::dbaccess
{
  class data_access_manager;

  using customer_manager_i = entity_manipulator<customer_t>;

  class customer_manager : public customer_manager_i
  {
  public:
    customer_manager() =default;
    ~customer_manager() =default;

    std::vector<customer_t> get_all() noexcept override;
    std::vector<customer_t> get_like(const customer_t &entity) noexcept override;
    customer_t get(int id) noexcept override;
    bool add(const customer_t &entity) noexcept override;
    bool modify(const customer_t &entity) noexcept override;
    bool remove(int id) noexcept override;

  private:
    data_access_manager*
    parent() noexcept;
    std::string
    glue_params(const customer_t &entity, std::string separator) noexcept;

  };
}
