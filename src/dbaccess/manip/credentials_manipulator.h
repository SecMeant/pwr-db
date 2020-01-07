#pragma once
#include "entity_manipulator.h"
#include "dbaccess/table/credentials.h"


namespace app::dbaccess
{
  class data_access_manager;

  using credentials_manipulator_i = entity_manipulator<credentials_t>;

  class credentials_manipulator : public credentials_manipulator_i
  {
  public:
    credentials_manipulator() =default;
    ~credentials_manipulator() =default;

    std::vector<credentials_t> get_all() noexcept override;
    std::vector<credentials_t> get_like(const credentials_t &entity) noexcept override;
    credentials_t get(int id) noexcept override;
    bool add(const credentials_t &entity) noexcept override;
    bool modify(const credentials_t &entity) noexcept override;
    bool remove(int id) noexcept override;

  private:
    data_access_manager*
    parent() noexcept;
    std::string
    glue_params(const credentials_t &entity, std::string separator) noexcept;

  };
}
