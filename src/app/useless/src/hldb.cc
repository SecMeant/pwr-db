#include "hldb.h"
#include "dbaccess/db_connection.h"
#include "dbaccess/db_defaults.h"
#include <fmt/format.h>

using namespace app::dbaccess;
using namespace app::dbaccess::defaults;
using namespace app::dbaccess;

namespace app::logic {
  hldb::hldb()
    : m_hr(*this)
    , m_offer_manager(*this)
    , m_reservatio_manager(*this)
    , m_session(*this)
  {}

  hldb::hldb(const std::string &database_name)
    : m_hr(*this)
    , m_offer_manager(*this)
    , m_reservatio_manager(*this)
    , m_session(*this)
  {
    m_dbconn = db_connection(DB_HOSTNAME,
                             database_name,
                             DB_PORT_NO,
                             { DB_USERNAME, DB_PASSWORD });

    if (m_dbconn)
      this->category_cache = this->get_all_category();

    if (this->category_cache.size() == 0)
      fmt::print(stderr, "Failed to fetch categories (size 0 retunred)\n");
  }

  std::vector<customer_t>
  hldb::get_all_customers()
  {
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->get_all();
  }

  std::vector<credentials_t>
  hldb::get_all_credentials()
  {
    const auto manip = db_access_manager.get_credentials_manipulator();
    return manip->get_all();
  }

  std::vector<offer_t>
  hldb::get_all_offers()
  {
    const auto manip = db_access_manager.get_offer_manipulator();
    return manip->get_all();
  }

  std::vector<employee_t>
  hldb::get_all_employees()
  {
    const auto manip = db_access_manager.get_employee_manipulator();
    return manip->get_all();
  }

  std::vector<tour_t>
  hldb::get_all_tours()
  {
    const auto manip = db_access_manager.get_tour_manipulator();
    return manip->get_all();
  }

  std::vector<customer_t>
  hldb::get_customers_like(const customer_t &inst)
  {
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->get_like(inst);
  }

  std::vector<credentials_t>
  hldb::get_credentials_like(const credentials_t &creds)
  {
    const auto manip = db_access_manager.get_credentials_manipulator();
    return manip->get_like(creds);
  }

  std::vector<offer_t>
  hldb::get_offers_like(const offer_t &inst)
  {
    const auto manip = db_access_manager.get_offer_manipulator();
    return manip->get_like(inst);
  }

  std::vector<employee_t>
  hldb::get_employees_like(const employee_t &inst)
  {
    const auto manip = db_access_manager.get_employee_manipulator();
    return manip->get_like(inst);
  }

  std::vector<tour_t>
  hldb::get_tours_like(const tour_t &inst)
  {
    const auto manip = db_access_manager.get_tour_manipulator();
    return manip->get_like(inst);
  }

  customer_t
  hldb::get_customers_like(int id)
  {
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->get(id);
  }

  credentials_t
  hldb::get_credentials_like(int id)
  {
    const auto manip = db_access_manager.get_credentials_manipulator();
    return manip->get(id);
  }

  offer_t
  hldb::get_offers_like(int id)
  {
    const auto manip = db_access_manager.get_offer_manipulator();
    return manip->get(id);
  }

  employee_t
  hldb::get_employees_like(int id)
  {
    const auto manip = db_access_manager.get_employee_manipulator();
    return manip->get(id);
  }

  tour_t
  hldb::get_tours_like(int id)
  {
    const auto manip = db_access_manager.get_tour_manipulator();
    return manip->get(id);
  }

  bool
  hldb::add_customer(const customer_t &inst)
  {
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->add(inst);
  }

  bool
  hldb::add_offer(const offer_t &inst)
  {
    const auto manip = db_access_manager.get_offer_manipulator();
    return manip->add(inst);
  }

  bool
  hldb::add_employee(const employee_t &inst)
  {
    const auto manip = db_access_manager.get_employee_manipulator();
    return manip->add(inst);
  }

  bool
  hldb::add_tour(const tour_t &inst)
  {
    const auto manip = db_access_manager.get_tour_manipulator();
    return manip->add(inst);
  }

  bool
  hldb::remove_customer(int id)
  {
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->remove(id);
  }

  bool
  hldb::remove_offer(int id)
  {
    const auto manip = db_access_manager.get_offer_manipulator();
    return manip->remove(id);
  }

  bool
  hldb::remove_employee(int id)
  {
    const auto manip = db_access_manager.get_employee_manipulator();
    return manip->remove(id);
  }

  bool
  hldb::remove_tour(int id)
  {
    const auto manip = db_access_manager.get_tour_manipulator();
    return manip->remove(id);
  }

  bool
  hldb::modify_customer(const customer_t &inst)
  {
    const auto manip = db_access_manager.get_customer_manipulator();
    return manip->modify(inst);
  }

  bool
  hldb::modify_offer(const offer_t &inst)
  {
    const auto manip = db_access_manager.get_offer_manipulator();
    return manip->modify(inst);
  }

  bool
  hldb::modify_employee(const employee_t &inst)
  {
    const auto manip = db_access_manager.get_employee_manipulator();
    return manip->modify(inst);
  }

  bool
  hldb::modify_tour(const tour_t &inst)
  {
    const auto manip = db_access_manager.get_tour_manipulator();
    return manip->modify(inst);
  }

  std::vector<dbaccess::category_t>
  hldb::get_all_category()
  {
    const auto manip = db_access_manager.get_category_manipulator();
    return manip->get_all();
  }

  std::vector<dbaccess::category_t>
  hldb::get_category_like(const dbaccess::category_t &inst)
  {
    const auto manip = db_access_manager.get_category_manipulator();
    return manip->get_like(inst);
  }

  dbaccess::category_t
  hldb::get_category_like(int id)
  {
    const auto manip = db_access_manager.get_category_manipulator();
    return manip->get(id);
  }

  bool
  hldb::add_category(const dbaccess::category_t &inst)
  {
    const auto manip = db_access_manager.get_category_manipulator();
    return manip->add(inst);
  }
  bool
  hldb::remove_category(int id)
  {
    const auto manip = db_access_manager.get_category_manipulator();
    return manip->remove(id);
  }

  bool
  hldb::modify_category(const dbaccess::category_t &inst)
  {
    const auto manip = db_access_manager.get_category_manipulator();
    return manip->modify(inst);
  }

  const employee_t &
  hldb::get_logged_user()
  {
    return m_session.current();
  }

  bool
  hldb::login(std::string_view login, std::string_view pass)
  {
    return m_session.authenticate(login, pass);
  }

  bool
  hldb::authenticate(std::string_view login, std::string_view pass)
  {
    return m_dbconn.authenticate(login, pass);
  }

  bool
  hldb::make_reservation(int off_id,
                         int cus_id,
                         int ticket_count,
                         bool insurance,
                         bool extra_meals)
  {
    return m_reservatio_manager.reserve_tour(
      off_id, cus_id, ticket_count, insurance, extra_meals);
  }

  bool
  hldb::drop_reservation(int id)
  {
    return m_reservatio_manager.resign(id);
  }

  bool
  hldb::modify_reservation(const dbaccess::tour_t &t1)
  {
    return m_reservatio_manager.modify(t1);
  }

  bool
  hldb::raw_query(const std::string &t1)
  {
    return m_dbconn.query(t1);
  }

  mysql_res_t
  hldb::raw_query_res(const std::string &t1)
  {
    return m_dbconn.query_res(t1);
  }

  std::string
  hldb::hash(std::string_view s)
  {
    constexpr auto query_template = "select password('{}');";

    auto res = this->raw_query_res(fmt::format(query_template, s));

    if (!res)
      return "";

    return mysql_fetch_row(res.get())[0] + 1;
  }

  category_t
  hldb::get_category_by_id(int id)
  {
    auto it = std::find_if(std::begin(this->category_cache),
                           std::end(this->category_cache),
                           [id](const auto &c) {return c.id == id;});

    if (it != std::end(this->category_cache))
      return *it;
    return {};
  }

  int
  hldb::get_category_id_by_name(std::string_view cat_name)
  {
    fmt::print("Looking for category name: {}\n", cat_name);
    auto it = std::find_if(std::begin(this->category_cache),
                           std::end(this->category_cache),
                           [cat_name](const auto &c) {
                           fmt::print("Catname :{}\n", c.name);
                           return c.name == cat_name;});

    if (it != std::end(this->category_cache))
      return it->id;
    return INVALID<int>;
  }

  privilege_level
  hldb::get_user_privilage()
  {
    return m_session.privilege();
  }
  bool
  hldb::change_offer(const dbaccess::offer_t &o1)
  {
    return m_offer_manager.modify(o1);
  }

  bool
  hldb::drop_offer(const dbaccess::offer_t &o1)
  {
    return m_offer_manager.drop_offer(o1.id);
  }

} // namespace app::logic
