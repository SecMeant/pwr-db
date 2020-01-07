#include "data_access_manager.h"
#include "../hldb.h"
#include "../reflect.h"
namespace app::dbaccess
{

  data_access_manager::data_access_manager()
  {
  }

  logic::hldb_i*
  data_access_manager::parent() noexcept
  {
    return container_of(this, logic::hldb, db_access_manager);
  }

  const customer_manipulator_i*
  data_access_manager::get_customer_manipulator()
  {
    return &m_customer_manipulator;
  }

  const employee_manipulator_i*
  data_access_manager::get_employee_manipulator()
  {
    return &m_employee_manipulator;
  }

  const offer_manipulator_i*
  data_access_manager::get_offer_manipulator()
  {
    return &m_offer_manipulator;
  }

  const tour_manipulator_i*
  data_access_manager::get_tour_manipulator()
  {
    return &m_tour_manipulator;
  }

  const credentials_manipulator_i*
  data_access_manager::get_credentials_manipulator()
  {
    return &m_credentials_manipulator;
  }
}