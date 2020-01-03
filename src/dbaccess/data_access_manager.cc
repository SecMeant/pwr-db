#include "data_access_manager.h"
#include "../hldb.h"
#include "../reflect.h"
namespace app::dbaccess
{

  data_access_manager::data_access_manager()
  {
    get_dbconn();

    customer_t cust{};
    m_customer_manager.get_all();
    m_customer_manager.get(1);
    m_customer_manager.get_like(cust);
    m_customer_manager.add(cust);
    m_customer_manager.modify(cust);
    m_customer_manager.remove(cust);
    
    employee_t emp{};
    m_employee_manager.get(1);
    m_employee_manager.get_all();
    m_employee_manager.get_like(emp);
    m_employee_manager.add(emp);
    m_employee_manager.modify(emp);
    m_employee_manager.remove(emp);


    offer_t off{};
    m_offer_manager.get_all();
    m_offer_manager.get_like(off);
    m_offer_manager.get(1);
    m_offer_manager.add(off);
    m_offer_manager.modify(off);
    m_offer_manager.remove(off);

    tour_t tou{};
    m_tour_manager.get_all();
    m_tour_manager.get_like(tou);
    m_tour_manager.get(1);
    m_tour_manager.add(tou);
    m_tour_manager.modify(tou);
    m_tour_manager.remove(tou);
  }

  logic::hldb*
  data_access_manager::parent() noexcept
  {
    return container_of(this, logic::hldb, db_access_manager);
  }

  db_connection_i* data_access_manager::get_dbconn()
  {
    return &this->parent()->m_dbconn;
  }
}