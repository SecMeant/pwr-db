#include "offer_manager.h"
#include "hldb.h"
#include "reflect.h"

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

    }

    bool offer_manager::modify(const offer_t &o1)
    {

    }

    logic::hldb*
    offer_manager::parent() noexcept
    {
       return container_of(this, logic::hldb, m_offer_manager);
    }

}