#include "data_access_manager.h"
#include "../hldb.h"
#include "../reflect.h"
namespace app::dbaccess
{

  data_access_manager::data_access_manager()
  {
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
  const customer_manipulator&
  data_access_manager::get_customer_manipulator()
  {
    return m_customer_manipulator;
  }
  const employee_manipulator&
  data_access_manager::get_employee_manipulator()
  {
    return m_employee_manipulator;
  }

  const offer_manipulator&
  data_access_manager::get_offer_manipulator()
  {
    return m_offer_manipulator;
  }

  const tour_manipulator&
  data_access_manager::get_tour_manipulator()
  {
    return m_tour_manipulator;
  }
}