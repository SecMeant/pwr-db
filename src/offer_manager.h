#pragma once
#include "dbaccess/table/category.h"
#include "dbaccess/table/offer.h"
#include "dbaccess/table/tour.h"
#include "dbaccess/date.h"
#include <string>

namespace app::logic
{
  class hldb_i;
  class offer_manager
  {
    hldb_i &parent;
  public:
    offer_manager(hldb_i&);
    ~offer_manager()=default;
    bool append_offer(const std::string &name,
                      const std::string &country,
                      const std::string city,
                      dbaccess::date_t begin,
                      dbaccess::date_t end,
                      int price,
                      int insurance_cost,
                      int extra_meals,
                      int ticket_count,
                      const std::string &cname);
    bool drop_offer(int tour_id);
    bool modify(const dbaccess::offer_t &t1);
    bool modify_2(const dbaccess::offer_t &t1);
  private:
    int callculate_cost_diff(const dbaccess::offer_t &o1, const dbaccess::offer_t &o2, dbaccess::tour_t &t);
   };
}