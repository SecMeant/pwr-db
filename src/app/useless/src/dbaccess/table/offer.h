#pragma once

#include "../date.h"
#include "dbaccess/table/valid.h"
#include <string>

namespace app::dbaccess {
  struct offer_t
  {
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
  };
} // namespace app::dbaccess
