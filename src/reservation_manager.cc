#include "reservation_manager.h"
#include "hldb.h"

using namespace app::dbaccess;
namespace app::logic
{
    void reservation_manager::reserve_tour(int off_id, int cus_id, int ticket_count, bool insurance, bool extra_meals)
    {
      auto hldb = parent();
      auto off = hldb->get.get_offers_like(off_id);

      if(!off.valid())
        return false;
      auto cus = hldb->get.get_customers_like(cus_id);

      if(!cus.valid())
        return false;

      auto usr = hldb->get.get_logged_user();
      auto t = prepare();
      if(!t.valid())
        return false;

      hldb.add_tour(t);
      return true;
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

    tour_t reservation_manager::prepare(offer_t& o,
                                      customer_t &c,
                                      employee_t &e,
                                      int ticket_count,
                                      bool insurance,
                                      bool extra_meals)
    {
      tour_t  tour;

      if(o.ticket_count < ticket_count)
        return tour;

      int final_debt =o.price*ticket_count;

      if(insurance)
        final_debt += ticket_count*o.insurance_cost;

      if(extra_meals)
        final_debt += ticket_count*o.extra_meals_cost;

      sql::set_any(tour.id); //ANY<int>;
      tour.debt = final_debt;
      tour.insurance = insurance;
      tour.extra_meals =extra_meals;
      tour.finished = 0;
      tour.reserved_tickets =ticket_count;
      tour.customersid = c.id;
      tour.employeesid = e.id;
      tour.offerid = o.id;
      return tour;
    }
}