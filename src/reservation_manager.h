#include "dbaccess/tour.h"
#include "dbaccess/offer.h"
#include "dbaccess/customer.h"

namespace app::logic
{
  class hldb;
  class reservation_manager
  {
  public:
    reservation_manager();
    ~reservation_manager();
    void make(offer_t&, customer_t&);
    void resign(tour_t&);
    void modify(tour_t&);
  private:
    logic::hldb*
    parent() noexcept;
  };
}