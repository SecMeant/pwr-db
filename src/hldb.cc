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
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->get_all();
  }

  std::vector<offer_t> hldb::get_all_offers()
  {
    const auto manip =db_access_manager.get_offer_manipulator();
    return manip->get_all();
  }

  std::vector<employee_t> hldb::get_all_employees()
  {
    const auto manip = db_access_manager.get_employee_manipulator();
    return manip->get_all();
  }

  std::vector<tour_t> hldb::get_all_tours()
  {
    const auto manip =db_access_manager.get_tour_manipulator();
    return manip->get_all();
  }

  std::vector<customer_t> hldb::get_customers_like(const customer_t& inst)
  {
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->get_like(inst);
  }

  std::vector<credentials_t> hldb::get_credentials_like(const credentials_t& creds)
  {
    const auto manip = db_access_manager.get_credentials_manipulator();
    return manip->get_like(creds);
  }

  std::vector<offer_t> hldb::get_offers_like(const offer_t& inst)
  {
    const auto manip =db_access_manager.get_offer_manipulator();
    return manip->get_like(inst);
  }

  std::vector<employee_t> hldb::get_employees_like(const employee_t& inst)
  {
    const auto manip = db_access_manager.get_employee_manipulator();
    return manip->get_like(inst);
  }

  std::vector<tour_t> hldb::get_tours_like(const tour_t& inst)
  {
    const auto manip =db_access_manager.get_tour_manipulator();
    return manip->get_like(inst);
  }

  customer_t hldb::get_customers_like(int id)
  {
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->get(id);
  }

  offer_t hldb::get_offers_like(int id)
  {
    const auto manip =db_access_manager.get_offer_manipulator();
    return manip->get(id);
  }

  employee_t hldb::get_employees_like(int id)
  {
    const auto manip = db_access_manager.get_employee_manipulator();
    return manip->get(id);
  }

  tour_t hldb::get_tours_like(int id)
  {
    const auto manip =db_access_manager.get_tour_manipulator();
    return manip->get(id);
  }

  bool hldb::add_customer(const customer_t& inst)
  {
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->add(inst);
  }

  bool hldb::add_offer(const offer_t& inst)
  {
    const auto manip =db_access_manager.get_offer_manipulator();
   return manip->add(inst);
  }

  bool hldb::add_employee(const employee_t& inst)
  {
    const auto manip = db_access_manager.get_employee_manipulator();
   return manip->add(inst);
  }

  bool hldb::add_tour(const tour_t& inst)
  {
    const auto manip =db_access_manager.get_tour_manipulator();
   return manip->add(inst);
  }

  bool hldb::remove_customer(int id)
  {
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->remove(id);
  }

  bool hldb::remove_offer(int id)
  {
    const auto manip =db_access_manager.get_offer_manipulator();
   return manip->remove(id);
  }

  bool hldb::remove_employee(int id)
  {
    const auto manip = db_access_manager.get_employee_manipulator();
   return manip->remove(id);
  }

  bool hldb::remove_tour(int id)
  {
    const auto manip =db_access_manager.get_tour_manipulator();
   return manip->remove(id);
  }

  bool hldb::modify_customer(const customer_t& inst)
  {
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->modify(inst);
  }

  bool hldb::modify_offer(const offer_t& inst)
  {
    const auto manip =db_access_manager.get_offer_manipulator();
   return manip->modify(inst);
  }

  bool hldb::modify_employee(const employee_t& inst)
  {
    const auto manip = db_access_manager.get_employee_manipulator();
   return manip->modify(inst);
  }

  bool hldb::modify_tour(const tour_t& inst)
  {
    const auto manip =db_access_manager.get_tour_manipulator();
    return manip->modify(inst);
  }

  std::vector<dbaccess::category_t> hldb::get_all_category()
  {
    const auto manip =db_access_manager.get_category_manipulator();
    return manip->get_all();
  }

  std::vector<dbaccess::category_t> hldb::get_category_like(const dbaccess::category_t&inst)
  {
    const auto manip =db_access_manager.get_category_manipulator();
    return manip->get_like(inst);
  }

  dbaccess::category_t hldb::get_category_like(int id)
  {
    const auto manip =db_access_manager.get_category_manipulator();
    return manip->get(id);
  }

  bool hldb::add_category(const dbaccess::category_t&inst)
  {
    const auto manip =db_access_manager.get_category_manipulator();
    return manip->add(inst);
  }
  bool hldb::remove_category(int id)
  {
    const auto manip =db_access_manager.get_category_manipulator();
    return manip->remove(id);
  }

  bool hldb::modify_category(const dbaccess::category_t&inst)
  {
    const auto manip =db_access_manager.get_category_manipulator();
    return manip->modify(inst);
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
    return m_reservatio_manager.reserve_tour(off_id,cus_id,ticket_count,insurance,extra_meals);
  }

  bool hldb::drop_reservation(int id)
  {
    return m_reservatio_manager.resign(id);
  }

  bool hldb::modify_reservation(const dbaccess::tour_t &t1)
  {
    return m_reservatio_manager.modify(t1);
  }

  bool hldb::raw_query(const std::string &t1)
  {
    return m_dbconn.query(t1);
  }

  mysql_res_t hldb::raw_query_res(const std::string &t1)
  {
    return m_dbconn.query_res(t1);
  }

}
