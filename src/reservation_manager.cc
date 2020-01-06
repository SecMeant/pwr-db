#include "reservation_manager.h"
#include "hldb.h"

namespace app::logic
{
    void reservation_manager::reserve_tour(offer_t& o, customer_t& c)
    {
      auto hldb = parent();
      auto off = hldb->get.get_offers_like(o);
      if(!off.valid())
        return false;
      auto cus = hldb->get.get_customers_like(c);
      if(!cus.valid())
        return false;
      auto usr = hldb->get.get_logged_user();
      tour_t
    }

    void reservation_manager::resign(tour_t&)
    {

    }

    void reservation_manager::modify(tour_t&)
    {

    }

    logic::hldb*
    reservation_manager::parent() noexcept
    {
       return container_of(this, logic::hldb, res_manager);
    }

}