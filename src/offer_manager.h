#pragma once
#include "dbaccess/table/category.h"
#include "dbaccess/table/offer.h"
#include "dbaccess/date.h"
#include <string>

namespace app::logic
{
  class hldb;
  class offer_manager
  {
  public:
    offer_manager()=default;
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
  private:
    hldb*
    parent() noexcept;
   };
}