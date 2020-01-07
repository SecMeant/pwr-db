#pragma once
#include "manip/customer_manager.h"
#include "manip/employee_manager.h"
#include "manip/offer_manager.h"
#include "manip/tour_manager.h"
#include "db_connection.h"

namespace app::logic
{
  class hldb;
}

namespace app::dbaccess
{
  class data_access_manager
  {

  public:
    customer_manager m_customer_manager;
    employee_manager m_employee_manager;
    offer_manager m_offer_manager;
    tour_manager m_tour_manager;
    data_access_manager();
    ~data_access_manager()=default;

    const customer_manager&
    get_customer_manipulator()
    {
      return this->m_customer_manager;
    }
    const employee_manager&
    get_employee_manipulator()
    {
      return this->m_employee_manager;
    }

    const offer_manager&
    get_offer_manipulator()
    {
      return this->m_offer_manager;
    }

    const tour_manager&
    get_tour_manipulator()
    {
      return this->m_tour_manager;
    }
    db_connection_i* get_dbconn();
  private:
    logic::hldb*
    parent() noexcept;
  };
}