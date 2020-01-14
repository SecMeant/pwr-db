#pragma once

#include "dbaccess/table/valid.h"

namespace app::dbaccess {

  struct tour_t
  {
    VALIDATABLE_BY(int, id)
    int debt;
    int insurance;
    int extra_meals;
    tour_state state;
    int customersid;
    int employeesid;
    int offerid;
    int reserved_tickets;

    bool operator==(const tour_t& rhs)const
    {
      return offerid == rhs.offerid;
    }

    inline static tour_t
    make_any()
    {
      tour_t ret;

      sql::set_any(ret.id);
      sql::set_any(ret.debt);
      sql::set_any(ret.insurance);
      sql::set_any(ret.extra_meals);
      sql::set_any(ret.state);
      sql::set_any(ret.customersid);
      sql::set_any(ret.employeesid);
      sql::set_any(ret.offerid);
      sql::set_any(ret.reserved_tickets);

      return ret;
    }
  };
} // namespace app::dbaccess
