#pragma once

#include "../date.h"

#include <string>

namespace app::dbaccess {
struct offer_t
{
  int id;
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
};
}