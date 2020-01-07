#pragma once
#include "dbaccess/table/tour.h"
#include "dbaccess/table/offer.h"
#include "dbaccess/table/employee.h"
#include "dbaccess/table/customer.h"

namespace app::logic
{
  class hldb;
  class reservation_manager
  {
  public:
    reservation_manager()=default;
    ~reservation_manager()=default;
    bool reserve_tour(int off_id, int cus_id, int ticket_count, bool insurance, bool extra_meals);
    bool resign(int tour_id);
    bool modify(const dbaccess::tour_t &t1);
  private:
    hldb*
    parent() noexcept;
    dbaccess::tour_t prepare( dbaccess::offer_t& o,
                    dbaccess::customer_t &c,
                    dbaccess::employee_t &e,
                    int ticket_count,
                    bool insurance,
                    bool extra_meals);
   };
}