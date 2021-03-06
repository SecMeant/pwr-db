#pragma once

#include "dbaccess/data_access_manager.h"
#include "dbaccess/db_connection.h"
#include "hr_manager.h"
#include "offer_manager.h"
#include "reservation_manager.h"
#include "session_manager.h"

namespace app::logic {

  class hldb_i
  {
  public:
    virtual std::vector<dbaccess::customer_t>
    get_all_customers() = 0;
    virtual std::vector<dbaccess::credentials_t>
    get_all_credentials() = 0;
    virtual std::vector<dbaccess::offer_t>
    get_all_offers() = 0;
    virtual std::vector<dbaccess::employee_t>
    get_all_employees() = 0;
    virtual std::vector<dbaccess::tour_t>
    get_all_tours() = 0;

    virtual std::vector<dbaccess::customer_t>
    get_customers_like(const dbaccess::customer_t &) = 0;
    virtual std::vector<dbaccess::credentials_t>
    get_credentials_like(const dbaccess::credentials_t &) = 0;
    virtual std::vector<dbaccess::offer_t>
    get_offers_like(const dbaccess::offer_t &) = 0;
    virtual std::vector<dbaccess::employee_t>
    get_employees_like(const dbaccess::employee_t &) = 0;
    virtual std::vector<dbaccess::tour_t>
    get_tours_like(const dbaccess::tour_t &) = 0;

    virtual dbaccess::customer_t
    get_customers_like(int id) = 0;
    virtual dbaccess::credentials_t
    get_credentials_like(int id) = 0;
    virtual dbaccess::offer_t
    get_offers_like(int id) = 0;
    virtual dbaccess::employee_t
    get_employees_like(int id) = 0;
    virtual dbaccess::tour_t
    get_tours_like(int id) = 0;

    virtual bool
    add_customer(const dbaccess::customer_t &) = 0;
    virtual bool
    add_offer(const dbaccess::offer_t &) = 0;
    virtual bool
    add_employee(const dbaccess::employee_t &) = 0;
    virtual bool
    add_tour(const dbaccess::tour_t &) = 0;

    virtual bool
    remove_customer(int id) = 0;
    virtual bool
    remove_offer(int id) = 0;
    virtual bool
    remove_employee(int id) = 0;
    virtual bool
    remove_tour(int id) = 0;

    virtual bool
    modify_customer(const dbaccess::customer_t &) = 0;
    virtual bool
    modify_offer(const dbaccess::offer_t &) = 0;
    virtual bool
    modify_employee(const dbaccess::employee_t &) = 0;
    virtual bool
    modify_tour(const dbaccess::tour_t &) = 0;
    virtual bool login(std::string_view, std::string_view) = 0;
    virtual bool authenticate(std::string_view, std::string_view) = 0;
    virtual bool
    make_reservation(int off_id,
                     int cus_id,
                     int ticket_count,
                     bool insurance,
                     bool extra_meals) = 0;
    virtual bool
    drop_reservation(int id) = 0;
    virtual bool
    modify_reservation(const dbaccess::tour_t &t1) = 0;
    virtual const dbaccess::employee_t &
    get_logged_user() = 0;
    virtual bool
    raw_query(const std::string &t1) = 0;
    virtual dbaccess::mysql_res_t
    raw_query_res(const std::string &t1) = 0;
    virtual std::vector<dbaccess::category_t>
    get_all_category() = 0;
    virtual std::vector<dbaccess::category_t>
    get_category_like(const dbaccess::category_t &) = 0;
    virtual dbaccess::category_t
    get_category_like(int id) = 0;
    virtual bool
    add_category(const dbaccess::category_t &) = 0;
    virtual bool
    remove_category(int id) = 0;
    virtual bool
    modify_category(const dbaccess::category_t &) = 0;
    virtual std::string
    hash(std::string_view s) = 0;
    virtual dbaccess::category_t
    get_category_by_id(int id) = 0;
    virtual int
    get_category_id_by_name(std::string_view catname) = 0;
    virtual ~hldb_i() = default;
    virtual privilege_level
    get_user_privilage()=0;
    virtual bool
    change_offer(const dbaccess::offer_t &t1) =0;

    virtual bool
    drop_offer(const dbaccess::offer_t &t1) =0;
  };

  class hldb : public hldb_i
  {
  public:
    hldb();
    hldb(const hldb&) = default;
    hldb(hldb&&) = default;
    hldb(const std::string &database_name);
    dbaccess::db_connection m_dbconn;
    session_manager m_session;
    reservation_manager m_reservatio_manager;
    offer_manager m_offer_manager;
    hr_manager m_hr;
    dbaccess::data_access_manager db_access_manager;
    std::vector<dbaccess::category_t> category_cache;

    std::vector<dbaccess::customer_t>
    get_all_customers();
    std::vector<dbaccess::credentials_t>
    get_all_credentials();
    std::vector<dbaccess::offer_t>
    get_all_offers();
    std::vector<dbaccess::employee_t>
    get_all_employees();
    std::vector<dbaccess::tour_t>
    get_all_tours();
    std::vector<dbaccess::category_t>
    get_all_category();

    std::vector<dbaccess::credentials_t>
    get_credentials_like(const dbaccess::credentials_t &);
    std::vector<dbaccess::customer_t>
    get_customers_like(const dbaccess::customer_t &);
    std::vector<dbaccess::offer_t>
    get_offers_like(const dbaccess::offer_t &);
    std::vector<dbaccess::employee_t>
    get_employees_like(const dbaccess::employee_t &);
    std::vector<dbaccess::tour_t>
    get_tours_like(const dbaccess::tour_t &);
    std::vector<dbaccess::category_t>
    get_category_like(const dbaccess::category_t &);

    dbaccess::customer_t
    get_customers_like(int id);
    dbaccess::credentials_t
    get_credentials_like(int id);
    dbaccess::offer_t
    get_offers_like(int id);
    dbaccess::employee_t
    get_employees_like(int id);
    dbaccess::tour_t
    get_tours_like(int id);
    dbaccess::category_t
    get_category_like(int id);

    bool
    add_customer(const dbaccess::customer_t &);
    bool
    add_offer(const dbaccess::offer_t &);
    bool
    add_employee(const dbaccess::employee_t &);
    bool
    add_tour(const dbaccess::tour_t &);
    bool
    add_category(const dbaccess::category_t &);

    bool
    remove_customer(int id);
    bool
    remove_offer(int id);
    bool
    remove_employee(int id);
    bool
    remove_tour(int id);
    bool
    remove_category(int id);

    bool
    modify_customer(const dbaccess::customer_t &);
    bool
    modify_offer(const dbaccess::offer_t &);
    bool
    modify_employee(const dbaccess::employee_t &);
    bool
    modify_tour(const dbaccess::tour_t &);
    bool
    modify_category(const dbaccess::category_t &);

    bool login(std::string_view, std::string_view);
    bool authenticate(std::string_view, std::string_view);
    bool
    make_reservation(int off_id,
                     int cus_id,
                     int ticket_count,
                     bool insurance,
                     bool extra_meals);
    bool
    drop_reservation(int id);
    bool
    modify_reservation(const dbaccess::tour_t &t1);

    bool
    change_offer(const dbaccess::offer_t &t1);
    bool
    drop_offer(const dbaccess::offer_t &t1);

    bool
    raw_query(const std::string &t1);
    dbaccess::mysql_res_t
    raw_query_res(const std::string &t1);

    const dbaccess::employee_t &
    get_logged_user();
    std::string
    hash(std::string_view s);
    dbaccess::category_t
    get_category_by_id(int id);
    int
    get_category_id_by_name(std::string_view cat_name);
    privilege_level
    get_user_privilage();
  };
} // namespace app::logic
