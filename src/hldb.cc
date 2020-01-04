#include "hldb.h"
using namespace app::dbaccess;

namespace app::logic
{
  std::vector<customer_t> hldb::get_all_customers()
  {
    return db_access_manager.m_customer_manager.get_all();
  }

  std::vector<offer_t> hldb::get_all_offers()
  {
    return db_access_manager.m_offer_manager.get_all();
  }

  std::vector<employee_t> hldb::get_all_employees()
  {
    return db_access_manager.m_employee_manager.get_all();
  }

  std::vector<tour_t> hldb::get_all_tours()
  {
    return db_access_manager.m_tour_manager.get_all();
  }

  std::vector<customer_t> hldb::get_customers_like(const customer_t& inst)
  {
    return db_access_manager.m_customer_manager.get_like(inst);
  }

  std::vector<offer_t> hldb::get_offers_like(const offer_t& inst)
  {
    return db_access_manager.m_offer_manager.get_like(inst);
  }

  std::vector<employee_t> hldb::get_employees_like(const employee_t& inst)
  {
    return db_access_manager.m_employee_manager.get_like(inst);
  }

  std::vector<tour_t> hldb::get_tours_like(const tour_t& inst)
  {
    return db_access_manager.m_tour_manager.get_like(inst);
  }

  customer_t hldb::get_customers_like(int id)
  {
    return db_access_manager.m_customer_manager.get(id);
  }

  offer_t hldb::get_offers_like(int id)
  {
    return db_access_manager.m_offer_manager.get(id);
  }

  employee_t hldb::get_employees_like(int id)
  {
    return db_access_manager.m_employee_manager.get(id);
  }

  tour_t hldb::get_tours_like(int id)
  {
    return db_access_manager.m_tour_manager.get(id);
  }

  void hldb::add_customer(const customer_t& inst)
  {
    db_access_manager.m_customer_manager.add(inst);
  }

  void hldb::add_offer(const offer_t& inst)
  {
    db_access_manager.m_offer_manager.add(inst);
  }

  void hldb::add_employee(const employee_t& inst)
  {
    db_access_manager.m_employee_manager.add(inst);
  }

  void hldb::add_tour(const tour_t& inst)
  {
    db_access_manager.m_tour_manager.add(inst);
  }

  void hldb::rmeove_customer(const customer_t& inst)
  {
    db_access_manager.m_customer_manager.remove(inst);
  }

  void hldb::rmeove_offer(const offer_t& inst)
  {
    db_access_manager.m_offer_manager.remove(inst);
  }

  void hldb::rmeove_employee(const employee_t& inst)
  {
    db_access_manager.m_employee_manager.remove(inst);
  }

  void hldb::rmeove_tour(const tour_t& inst)
  {
    db_access_manager.m_tour_manager.remove(inst);
  }

  void hldb::modify_customer(const customer_t& inst)
  {
    db_access_manager.m_customer_manager.modify(inst);
  }

  void hldb::modify_offer(const offer_t& inst)
  {
    db_access_manager.m_offer_manager.modify(inst);
  }

  void hldb::modify_employee(const employee_t& inst)
  {
    db_access_manager.m_employee_manager.modify(inst);
  }

  void hldb::modify_tour(const tour_t& inst)
  {
    db_access_manager.m_tour_manager.modify(inst);
  }

}