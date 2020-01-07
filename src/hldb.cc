#include "hldb.h"
#include "dbaccess/db_defaults.h"
#include "dbaccess/db_connection.h"
using namespace app::dbaccess;
using namespace app::dbaccess::defaults;
using namespace app::dbaccess;
namespace app::logic
{
  hldb::hldb(const std::string &database_name)
  {
    m_dbconn = db_connection(
       DB_HOSTNAME, database_name, DB_PORT_NO, { DB_USERNAME, DB_PASSWORD });
  }

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

  bool hldb::add_customer(const customer_t& inst)
  {
   return db_access_manager.m_customer_manager.add(inst);
  }

  bool hldb::add_offer(const offer_t& inst)
  {
   return db_access_manager.m_offer_manager.add(inst);
  }

  bool hldb::add_employee(const employee_t& inst)
  {
   return db_access_manager.m_employee_manager.add(inst);
  }

  bool hldb::add_tour(const tour_t& inst)
  {
   return db_access_manager.m_tour_manager.add(inst);
  }

  bool hldb::remove_customer(int id)
  {
   return db_access_manager.m_customer_manager.remove(id);
  }

  bool hldb::remove_offer(int id)
  {
   return db_access_manager.m_offer_manager.remove(id);
  }

  bool hldb::remove_employee(int id)
  {
   return db_access_manager.m_employee_manager.remove(id);
  }

  bool hldb::remove_tour(int id)
  {
   return db_access_manager.m_tour_manager.remove(id);
  }

  bool hldb::modify_customer(const customer_t& inst)
  {
   return db_access_manager.m_customer_manager.modify(inst);
  }

  bool hldb::modify_offer(const offer_t& inst)
  {
   return db_access_manager.m_offer_manager.modify(inst);
  }

  bool hldb::modify_employee(const employee_t& inst)
  {
   return db_access_manager.m_employee_manager.modify(inst);
  }

  bool hldb::modify_tour(const tour_t& inst)
  {
   return db_access_manager.m_tour_manager.modify(inst);
  }

  const employee_t& hldb::get_logged_user()
  {
    return m_session.current();
  }

  bool hldb::authenticate(std::string_view login, std::string_view pass)
  {
    return m_session.authenticate(login, pass);
  }
  bool hldb::make_reservation(int off_id, int cus_id, int ticket_count, bool insurance, bool extra_meals)
  {
    return res_manager.reserve_tour(off_id,cus_id,ticket_count,insurance,extra_meals);
  }

  bool hldb::drop_reservation(int id)
  {
    return res_manager.resign(id);
  }

  bool hldb::modify_reservation(dbaccess::tour_t &t1)
  {
    return res_manager.modify(t1);
  }
}