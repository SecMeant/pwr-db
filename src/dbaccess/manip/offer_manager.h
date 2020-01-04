#pragma once
#include "entity_manipulator.h"
#include "../offer.h"


namespace app::dbaccess
{
  class data_access_manager;

  class offer_manager_i : public entity_manipulator<offer_t>
  {
  public:
    virtual std::vector<offer_t> get_all() noexcept = 0;
    virtual std::vector<offer_t> get_like(const offer_t &entity) noexcept = 0;
    virtual offer_t get(int id) noexcept = 0;
    virtual void add(const offer_t &entity) noexcept = 0;
    virtual void modify(const offer_t &entity) noexcept = 0;
    virtual void remove(const offer_t &entity) noexcept = 0;
  };

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