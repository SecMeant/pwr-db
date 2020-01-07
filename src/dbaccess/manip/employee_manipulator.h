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

    std::vector<employee_t> get_all()const noexcept override;
    std::vector<employee_t> get_like(const employee_t &entity)const noexcept override;
    employee_t get(int id)const noexcept override;
    bool add(const employee_t &entity)const noexcept override;
    bool modify(const employee_t &entity)const noexcept override;
    bool remove(int id)const noexcept override;

  private:
    data_access_manager*
    parent()const noexcept;
    std::string
    glue_params(const employee_t &entity, std::string separator)const noexcept;

  };
}
