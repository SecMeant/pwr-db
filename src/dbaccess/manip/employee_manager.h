#pragma once
#include "entity_manipulator.h"
#include "../employee.h"


namespace app::dbaccess
{
  class data_access_manager;

  using employee_manager_i = entity_manipulator<employee_t>;

  class employee_manager : public employee_manager_i
  {
  public:
    employee_manager() =default;
    ~employee_manager() =default;

    std::vector<employee_t> get_all() noexcept override;
    std::vector<employee_t> get_like(const employee_t &entity) noexcept override;
    employee_t get(int id) noexcept override;
    void add(const employee_t &entity) noexcept override;
    void modify(const employee_t &entity) noexcept override;
    void remove(const employee_t &entity) noexcept override;

  private:
    data_access_manager*
    parent() noexcept;
    std::string
    glue_params(const employee_t &entity, std::string separator) noexcept;

  };
}
