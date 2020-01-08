#pragma once
#include "entity_manipulator.h"
#include "dbaccess/table/category.h"


namespace app::dbaccess
{
  class data_access_manager;

  using category_manipulator_i = entity_manipulator<category_t>;

  class category_manipulator : public category_manipulator_i
  {
  public:
    category_manipulator() =default;
    ~category_manipulator() =default;

    std::vector<category_t> get_all() const noexcept override;
    std::vector<category_t> get_like(const category_t &entity) const noexcept override;
    category_t get(int id) const noexcept override;
    bool add(const category_t &entity) const noexcept override;
    bool modify(const category_t &entity) const noexcept override;
    bool remove(int id) const noexcept override;

    data_access_manager*
    parent()const noexcept;
  private:
    std::string
    glue_params(const category_t &entity, std::string separator)const noexcept;

  };
}