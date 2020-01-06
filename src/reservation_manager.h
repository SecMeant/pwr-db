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
    void reserve_tour(dbaccess::offer_t&, dbaccess::customer_t&);
    void resign(dbaccess::tour_t&);
    void modify(dbaccess::tour_t&);
  private:
    hldb*
    parent() noexcept;
  };
}