#include "reservation_manager.h"
#include "hldb.h"
#include "reflect.h"
using namespace app::dbaccess;
namespace app::logic
{
    bool reservation_manager::reserve_tour(int off_id, int cus_id, int ticket_count, bool insurance, bool extra_meals)
    {
      auto hldb = parent();
      auto o = hldb->get_offers_like(off_id);

      if(!o.valid())
        return false;
      auto c = hldb->get_customers_like(cus_id);

      if(!c.valid())
        return false;

      auto e = hldb->get_logged_user();
      auto t = prepare(o,c,e,ticket_count,insurance,extra_meals);
      if(!t.valid())
        return false;

      hldb->add_tour(t);
      return true;
    }

    bool reservation_manager::resign(int tour_id)
    {
      auto hldb = parent();
      auto t = hldb->get_tours_like(tour_id);
      if(!t.valid())
        return false;
      auto o = hldb->get_offers_like(t.offerid);
      if(!o.valid())
        return false;
      o.tickets_count += t.reserved_tickets;
      t.state = tour_state::RESIGNED;
      hldb->modify_offer(o);
      hldb->modify_tour(t);
      return true;
    }

    bool reservation_manager::modify(const tour_t &t1)
    {
      auto hldb = parent();
      auto t2 = hldb->get_tours_like(t1.id);
      if(!t2.valid())
        return false;
      int ticket_diff = t1.reserved_tickets - t2.reserved_tickets;
      if(ticket_diff != 0)
      {
        auto o = hldb->get_offers_like(t2.offerid);
        if(!o.valid())
          return false;
        o.tickets_count -= ticket_diff;
        hldb->modify_offer(o);
      }
      hldb->modify_tour(t1);
      return true;
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
      // trigger in databesd should autmaticly decrease ticket count
      if(o.tickets_count < ticket_count)
        return tour;

      int final_debt =o.price*ticket_count;

      if(insurance)
        final_debt += ticket_count*o.insurance_cost;

      if(extra_meals)
        final_debt += ticket_count*o.extra_meals_cost;

      sql::set_any(tour.id);
      tour.debt = final_debt;
      tour.insurance = insurance;
      tour.extra_meals =extra_meals;
      tour.state = tour_state::UNFINSHED;
      tour.reserved_tickets =ticket_count;
      tour.customersid = c.id;
      tour.employeesid = e.id;
      tour.offerid = o.id;
      return tour;
    }
}