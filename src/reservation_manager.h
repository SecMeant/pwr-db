#include "dbaccess/table/tour.h"
#include "dbaccess/table/offer.h"
#include "dbaccess/table/customer.h"

namespace app::logic
{
  class hldb;
  class reservation_manager
  {
  public:
    reservation_manager();
    ~reservation_manager();
    void reserve_tour(int off_id, int cus_id, int ticket_count);
    void resign(int tour_id);
    void modify(int tour_id);
  private:
    hldb*
    parent() noexcept;
     bool reserve(dbaccess::offer_t& o,
                  dbaccess::customer_t &c,
                  dbaccess::employee_t &e,
                  int ticket_count,
                  bool insurance,
                  bool extra_meals);
   };
}