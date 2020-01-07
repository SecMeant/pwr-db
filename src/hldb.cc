#include "hldb.h"
using namespace app::dbaccess;

namespace app::logic
{
  std::vector<customer_t> hldb::get_all_customers()
  {
    return db_access_manager.m_customer_manipulator.get_all();
  }

  std::vector<offer_t> hldb::get_all_offers()
  {
    return db_access_manager.m_offer_manipulator.get_all();
  }

  std::vector<employee_t> hldb::get_all_employees()
  {
    return db_access_manager.m_employee_manipulator.get_all();
  }

  std::vector<tour_t> hldb::get_all_tours()
  {
    return db_access_manager.m_tour_manipulator.get_all();
  }

  std::vector<customer_t> hldb::get_customers_like(const customer_t& inst)
  {
    return db_access_manager.m_customer_manipulator.get_like(inst);
  }

  std::vector<offer_t> hldb::get_offers_like(const offer_t& inst)
  {
    return db_access_manager.m_offer_manipulator.get_like(inst);
  }

  std::vector<employee_t> hldb::get_employees_like(const employee_t& inst)
  {
    return db_access_manager.m_employee_manipulator.get_like(inst);
  }

  std::vector<tour_t> hldb::get_tours_like(const tour_t& inst)
  {
    return db_access_manager.m_tour_manipulator.get_like(inst);
  }

  customer_t hldb::get_customers_like(int id)
  {
    return db_access_manager.m_customer_manipulator.get(id);
  }

  offer_t hldb::get_offers_like(int id)
  {
    return db_access_manager.m_offer_manipulator.get(id);
  }

  employee_t hldb::get_employees_like(int id)
  {
    return db_access_manager.m_employee_manipulator.get(id);
  }

  tour_t hldb::get_tours_like(int id)
  {
    return db_access_manager.m_tour_manipulator.get(id);
  }

  bool hldb::add_customer(const customer_t& inst)
  {
   return db_access_manager.m_customer_manipulator.add(inst);
  }

  bool hldb::add_offer(const offer_t& inst)
  {
   return db_access_manager.m_offer_manipulator.add(inst);
  }

  bool hldb::add_employee(const employee_t& inst)
  {
   return db_access_manager.m_employee_manipulator.add(inst);
  }

  bool hldb::add_tour(const tour_t& inst)
  {
   return db_access_manager.m_tour_manipulator.add(inst);
  }

  bool hldb::remove_customer(int id)
  {
   return db_access_manager.m_customer_manipulator.remove(id);
  }

  bool hldb::remove_offer(int id)
  {
   return db_access_manager.m_offer_manipulator.remove(id);
  }

  bool hldb::remove_employee(int id)
  {
   return db_access_manager.m_employee_manipulator.remove(id);
  }

  bool hldb::remove_tour(int id)
  {
   return db_access_manager.m_tour_manipulator.remove(id);
  }

  bool hldb::modify_customer(const customer_t& inst)
  {
   return db_access_manager.m_customer_manipulator.modify(inst);
  }

  bool hldb::modify_offer(const offer_t& inst)
  {
   return db_access_manager.m_offer_manipulator.modify(inst);
  }

  bool hldb::modify_employee(const employee_t& inst)
  {
   return db_access_manager.m_employee_manipulator.modify(inst);
  }

  bool hldb::modify_tour(const tour_t& inst)
  {
   return db_access_manager.m_tour_manipulator.modify(inst);
  }
  const employee_t& hldb::get_logged_user()
  {
    return m_session.current();
  }

}
