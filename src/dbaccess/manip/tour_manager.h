#pragma once
#include "entity_manipulator.h"
#include "dbaccess/table/tour.h"
#include <string>

namespace app::dbaccess
{
  class data_access_manager;

  using tour_manager_i = entity_manipulator<tour_t>;

  class tour_manager : public tour_manager_i
  {
  public:
    tour_manager() =default;
    ~tour_manager() =default;

    std::vector<tour_t> get_all() noexcept override;
    std::vector<tour_t> get_like(const tour_t &entity) noexcept override;
    tour_t get(int id) noexcept override;
    void add(const tour_t &entity) noexcept override;
    void modify(const tour_t &entity) noexcept override;
    void remove(const tour_t &entity) noexcept override;

  private:
    data_access_manager*
    parent() noexcept;
    std::string
    glue_params(const tour_t &entity, std::string separator) noexcept;

  };
}
