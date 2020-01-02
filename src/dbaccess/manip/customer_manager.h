#pragma once
#include "entity_manipulator.h"
#include "../customer.h"


namespace app::dbaccess 
{
  class data_access_manager;

  class customer_manager_i : public entity_manipulator<customer_t>
  {
  public:
    virtual std::vector<customer_t> get_all() noexcept = 0;
    virtual std::vector<customer_t> get_like(const customer_t &entity) noexcept = 0;
    virtual customer_t get(int id) noexcept = 0;
    virtual void add(const customer_t &entity) noexcept = 0;
    virtual void modify(const customer_t &entity) noexcept = 0;
    virtual void remove(const customer_t &entity) noexcept = 0;
  };

  class customer_manager : public customer_manager_i
  {
  public:
    customer_manager() =default;
    ~customer_manager() =default;

    std::vector<customer_t> get_all() noexcept override;
    std::vector<customer_t> get_like(const customer_t &entity) noexcept override;
    customer_t get(int id) noexcept override;
    void add(const customer_t &entity) noexcept override;
    void modify(const customer_t &entity) noexcept override;
    void remove(const customer_t &entity) noexcept override; 
    
  private:
    data_access_manager*
    parent() noexcept;

  };
}