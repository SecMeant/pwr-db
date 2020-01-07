#pragma once

#include "dbaccess/db_connection.h"
#include "session_manager.h"
#include "reservation_manager.h"
#include "dbaccess/data_access_manager.h"

namespace app::logic {

  class hldb_i
  {
  public:
    virtual std::vector<dbaccess::customer_t> get_all_customers()=0;
    virtual std::vector<dbaccess::offer_t> get_all_offers()=0;
    virtual std::vector<dbaccess::employee_t> get_all_employees()=0;
    virtual std::vector<dbaccess::tour_t> get_all_tours()=0;

    virtual std::vector<dbaccess::customer_t> get_customers_like(const dbaccess::customer_t&)=0;
    virtual std::vector<dbaccess::offer_t> get_offers_like(const dbaccess::offer_t&)=0;
    virtual std::vector<dbaccess::employee_t> get_employees_like(const dbaccess::employee_t&)=0;
    virtual std::vector<dbaccess::tour_t> get_tours_like(const dbaccess::tour_t&)=0;

    virtual dbaccess::customer_t get_customers_like(int id)=0;
    virtual dbaccess::offer_t get_offers_like(int id)=0;
    virtual dbaccess::employee_t get_employees_like(int id)=0;
    virtual dbaccess::tour_t get_tours_like(int id)=0;

    virtual bool add_customer(const dbaccess::customer_t&)=0;
    virtual bool add_offer(const dbaccess::offer_t&)=0;
    virtual bool add_employee(const dbaccess::employee_t&)=0;
    virtual bool add_tour(const dbaccess::tour_t&)=0;

    virtual bool remove_customer(int id)=0;
    virtual bool remove_offer(int id)=0;
    virtual bool remove_employee(int id)=0;
    virtual bool remove_tour(int id)=0;

    virtual bool modify_customer(const dbaccess::customer_t&)=0;
    virtual bool modify_offer(const dbaccess::offer_t&)=0;
    virtual bool modify_employee(const dbaccess::employee_t&)=0;
    virtual bool modify_tour(const dbaccess::tour_t&)=0;
    virtual const dbaccess::employee_t& get_logged_user()=0;
  };

  class hldb : public hldb_i
  {
  public:
    dbaccess::db_connection m_dbconn;
    session_manager m_session;
    reservation_manager res_manager;
    dbaccess::data_access_manager db_access_manager;

    std::vector<dbaccess::customer_t> get_all_customers();
    std::vector<dbaccess::offer_t> get_all_offers();
    std::vector<dbaccess::employee_t> get_all_employees();
    std::vector<dbaccess::tour_t> get_all_tours();

    std::vector<dbaccess::customer_t> get_customers_like(const dbaccess::customer_t&);
    std::vector<dbaccess::offer_t> get_offers_like(const dbaccess::offer_t&);
    std::vector<dbaccess::employee_t> get_employees_like(const dbaccess::employee_t&);
    std::vector<dbaccess::tour_t> get_tours_like(const dbaccess::tour_t&);

    dbaccess::customer_t get_customers_like(int id);
    dbaccess::offer_t get_offers_like(int id);
    dbaccess::employee_t get_employees_like(int id);
    dbaccess::tour_t get_tours_like(int id);

    bool add_customer(const dbaccess::customer_t&);
    bool add_offer(const dbaccess::offer_t&);
    bool add_employee(const dbaccess::employee_t&);
    bool add_tour(const dbaccess::tour_t&);

    bool remove_customer(int id);
    bool remove_offer(int id);
    bool remove_employee(int id);
    bool remove_tour(int id);

    bool modify_customer(const dbaccess::customer_t&);
    bool modify_offer(const dbaccess::offer_t&);
    bool modify_employee(const dbaccess::employee_t&);
    bool modify_tour(const dbaccess::tour_t&);

    const dbaccess::employee_t& get_logged_user();
  };
}
