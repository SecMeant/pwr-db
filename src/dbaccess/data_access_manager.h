#pragma once
#include "manip/customer_manipulator.h"
#include "manip/employee_manipulator.h"
#include "manip/offer_manipulator.h"
#include "manip/tour_manipulator.h"
#include "manip/credentials_manipulator.h"
#include "manip/category_manipulator.h"
#include "db_connection.h"
#include <memory>
namespace app::logic
{
  class hldb_i;
}

namespace app::dbaccess
{
  class data_access_manager
  {
    friend data_access_manager* customer_manipulator::parent()const noexcept;
    friend data_access_manager* employee_manipulator::parent()const noexcept;
    friend data_access_manager* offer_manipulator::parent()const noexcept;
    friend data_access_manager* tour_manipulator::parent()const noexcept;
    friend data_access_manager* category_manipulator::parent()const noexcept;
    friend data_access_manager* credentials_manipulator::parent()const noexcept;
    customer_manipulator m_customer_manipulator;
    category_manipulator m_category_manipulator;
    credentials_manipulator m_credentials_manipulator;
    employee_manipulator m_employee_manipulator;
    offer_manipulator m_offer_manipulator;
    tour_manipulator m_tour_manipulator;
  public:
    data_access_manager();
    ~data_access_manager()=default;

    const customer_manipulator_i*
    get_customer_manipulator();

    const employee_manipulator_i*
    get_employee_manipulator();

    const offer_manipulator_i*
    get_offer_manipulator();

    const tour_manipulator_i*
    get_tour_manipulator();

    const credentials_manipulator_i*
    get_credentials_manipulator();

    const category_manipulator_i*
    get_category_manipulator();

    logic::hldb_i*
    parent() noexcept;

  };
}
