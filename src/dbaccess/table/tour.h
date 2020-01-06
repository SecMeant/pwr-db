#pragma once

#include "dbaccess/table/valid.h"

namespace app::dbaccess {
struct tour_t
{
  VALIDATABLE_BY(int, id)
  int debt;
  int insurance;
  int extra_meals;
  int finished;
  int customersid;
  int employeesid;
  int offerid;
  int reserved_tickets;
};
}