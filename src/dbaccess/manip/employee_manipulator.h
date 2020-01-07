#pragma once
#include "entity_manipulator.h"
#include "dbaccess/table/employee.h"


namespace app::dbaccess
{
  class data_access_manager;

  using employee_manipulator_i = entity_manipulator<employee_t>;

  class employee_manipulator : public employee_manipulator_i
  {
  public:
    employee_manipulator() =default;
    ~employee_manipulator() =default;

    std::vector<employee_t> get_all() noexcept override;
    std::vector<employee_t> get_like(const employee_t &entity) noexcept override;
    employee_t get(int id) noexcept override;
    bool add(const employee_t &entity) noexcept override;
    bool modify(const employee_t &entity) noexcept override;
    bool remove(int id) noexcept override;

  private:
    data_access_manager*
    parent() noexcept;
    std::string
    glue_params(const employee_t &entity, std::string separator) noexcept;

  };
}
