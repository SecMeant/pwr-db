#include "offer_manager.h"
#include "hldb.h"
#include "reflect.h"
#include <fmt/format.h>
using namespace app::dbaccess;
namespace app::logic
{
    bool offer_manager::append_offer(const std::string &name,
                                     const std::string &country,
                                     const std::string city,
                                     date_t begin,
                                     date_t end,
                                     int price,
                                     int insurance_cost,
                                     int extra_meals,
                                     int ticket_count,
                                     const std::string &cname)
    {
      auto hldb = parent();
      category_t cat;
      cat.name = cname;
      auto categories = hldb->get_category_like(cat);
      if(categories.size() == 0)
        return false;
      cat = categories[0];
      offer_t off;
      off.name = name;
      off.country = country;
      off.city = city;
      off.date_begin = begin;
      off.date_end = end;
      off.price = price;
      off.insurance_cost = insurance_cost;
      off.extra_meals_cost = extra_meals;
      off.tickets_count = ticket_count;
      off.categoryid = cat.id;
      return true;
    }

    bool offer_manager::drop_offer(int offer_id)
    {
      auto hldb = parent();
      tour_t tour;

      offer_t offer = hldb->get_offers_like(offer_id);
      if(!offer.valid())
        return false;
      app::sql::set_any(tour.id);
      app::sql::set_any(tour.insurance);
      app::sql::set_any(tour.extra_meals);
      app::sql::set_any(tour.state);
      app::sql::set_any(tour.customersid);
      app::sql::set_any(tour.employeesid);
      app::sql::set_any(tour.debt);
      app::sql::set_any(tour.reserved_tickets);
      tour.offerid = offer_id;
      auto tours = hldb->get_tours_like(tour);
      for(auto t = tours.begin(); t!= tours.end(); t++)
      {
        auto to_return = callculate_cost_diff(offer,offer,*t);
        hldb->modify_tour(*t);
      }
      return true;
    }

    bool offer_manager::modify(const offer_t &offer_1)
    {
      auto hldb = parent();
      offer_t offer_2 = hldb->get_offers_like(offer_1.id);
      if(!offer_2.valid())
        return false;
      tour_t tour;
      app::sql::set_any(tour.id);
      app::sql::set_any(tour.insurance);
      app::sql::set_any(tour.extra_meals);
      app::sql::set_any(tour.state);
      app::sql::set_any(tour.customersid);
      app::sql::set_any(tour.employeesid);
      app::sql::set_any(tour.debt);
      app::sql::set_any(tour.reserved_tickets);
      tour.offerid = offer_1.id;
      auto tours = hldb->get_tours_like(tour);

      for(auto t = tours.begin(); t!= tours.end(); t++)
      {
        t->debt = callculate_cost_diff(offer_1,offer_2,*t);
        hldb->modify_tour(*t);
      }
      hldb->modify_offer(offer_1);
      return true;
    }

    bool offer_manager::modify_2(const offer_t &offer)
    {
      auto hldb = parent();
      bool status =  hldb->raw_query(fmt::format("call modify_offer({},'{}','{}','{}',str_to_date('{}','%d.%m.%y'),str_to_date('{}','%d.%m.%y'),{},{},{},{});",offer.id,
                                  offer.name,
                                  offer.country,
                                  offer.city,
                                  str2base_str(epoch2str(offer.date_begin)),
                                  str2base_str(epoch2str(offer.date_end)),
                                  offer.price,
                                  offer.insurance_cost,
                                  offer.extra_meals_cost,
                                  offer.tickets_count,
                                  offer.categoryid));
    return status;
    }

    logic::hldb*
    offer_manager::parent() noexcept
    {
       return container_of(this, logic::hldb, m_offer_manager);
    }
    int callculate_cost_diff(offer_t &o_new, offer_t &o_old, tour_t &t)
    {
      int max_old_cost = o_old.price;
      if(t.insurance)
        max_old_cost +=o_old.insurance_cost;
      if(t.extra_meals)
        max_old_cost = o_old.extra_meals_cost;

      int payed = max_old_cost - t.debt;
      int cost_diff = (o_new.price - o_old.price);
      if(t.insurance)
        cost_diff += o_new.insurance_cost - o_old.insurance_cost;
      if(t.extra_meals)
        cost_diff+= o_new.extra_meals_cost - o_old.extra_meals_cost;
      return cost_diff-payed;
    }

}