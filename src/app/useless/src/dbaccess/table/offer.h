#pragma once

#include "../date.h"
#include "dbaccess/table/valid.h"
#include <string>

namespace app::dbaccess {
  struct offer_t
  {
    static constexpr size_t field_count = 11;

    VALIDATABLE_BY(int, id);
    std::string name;
    std::string country;
    std::string city;
    date_t date_begin;
    date_t date_end;
    int price;
    int insurance_cost;
    int extra_meals_cost;
    int categoryid;
    int tickets_count;

    bool operator==(const offer_t&rhs)const {
      return this->name == rhs.name;
    }

    inline static offer_t
    make_any()
    {
      offer_t ret;

      sql::set_any(ret.id);
      sql::set_any(ret.name);
      sql::set_any(ret.country);
      sql::set_any(ret.city);
      sql::set_any(ret.date_begin);
      sql::set_any(ret.date_end);
      sql::set_any(ret.price);
      sql::set_any(ret.insurance_cost);
      sql::set_any(ret.extra_meals_cost);
      sql::set_any(ret.categoryid);
      sql::set_any(ret.tickets_count);

      return ret;
    }
  };
} // namespace app::dbaccess
