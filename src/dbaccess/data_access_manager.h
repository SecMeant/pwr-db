#pragma once
#include "manip/customer_manipulator.h"
#include "manip/employee_manipulator.h"
#include "manip/offer_manipulator.h"
#include "manip/tour_manipulator.h"
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
    customer_manipulator m_customer_manipulator;
    employee_manipulator m_employee_manipulator;
    offer_manipulator m_offer_manipulator;
    tour_manipulator m_tour_manipulator;
    data_access_manager();
    ~data_access_manager()=default;

    const customer_manipulator&
    get_customer_manipulator();

    const employee_manipulator&
    get_employee_manipulator();

    const offer_manipulator&
    get_offer_manipulator();

    const tour_manipulator&
    get_tour_manipulator();

    db_connection_i* get_dbconn();
  private:
    logic::hldb*
    parent() noexcept;
  };
}
