#pragma once
#include "entity_manipulator.h"
#include "../employee.h"


namespace app::dbaccess
{
  class data_access_manager;

  class employee_manager_i : public entity_manipulator<employee_t>
  {
  public:
    virtual std::vector<employee_t> get_all() noexcept = 0;
    virtual std::vector<employee_t> get_like(const employee_t &entity) noexcept = 0;
    virtual employee_t get(int id) noexcept = 0;
    virtual void add(const employee_t &entity) noexcept = 0;
    virtual void modify(const employee_t &entity) noexcept = 0;
    virtual void remove(const employee_t &entity) noexcept = 0;
  };

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