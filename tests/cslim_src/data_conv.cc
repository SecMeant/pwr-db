extern "C"
{
#include <CSlim/Fixtures.h>
#include <CSlim/SlimList.h>
#include <CSlim/compatibility.h>
}

#include "dbaccess/date.h"
#include "dbaccess/db_connection.h"
#include "dbaccess/db_defaults.h"
#include "hldb.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <string>

using namespace app::dbaccess;

#ifndef CPP_COMPILING
extern "C" {
#endif

typedef struct date_info
{
  time_t epoch_int;
  std::string datestr;
  char result[32];
} date;

static const char *
set_Epoch_date(void *void_self, SlimList *args)
{
  date *self = (date *)void_self;
  self->epoch_int = atoll(SlimList_GetStringAt(args, 0));
  return self->result;
}

static const char *
epoch2date(void *void_self, SlimList *args)
{
  date *self = (date *)void_self;
  auto date_s = app::dbaccess::date_t(tb(self->epoch_int));
  auto strdate = epoch2str(date_s);
  std::copy_n(std::begin(strdate), std::min(sizeof(self->result), strdate.size()), self->result);
  return self->result;
}

static const char *
set_Date_str(void *void_self, SlimList *args)
{
  date *self = (date *)void_self;
  self->datestr = SlimList_GetStringAt(args, 0);
  return self->result;
}

static const char *
date2epoch(void *void_self, SlimList *args)
{
  date *self = (date *)void_self;
  auto strdate = self->datestr;
  auto epoch = str2epoch(strdate);
  sprintf(self->result, "%li", epoch.time_since_epoch().count());
  return self->result;
}

void* Date_Conversion_Create(StatementExecutor* errorHandler, SlimList* args)
{
  date_info* self = new date_info;
  self->result[0] = 0;
  return self;
}

void Date_Conversion_Destroy(void* void_self)
{
  date_info* self = (date_info*)void_self;
  delete self;
}

SLIM_CREATE_FIXTURE(Date_Conversion)
SLIM_FUNCTION(set_Epoch_date);
SLIM_FUNCTION(set_Date_str);
SLIM_FUNCTION(epoch2date);
SLIM_FUNCTION(date2epoch);
SLIM_END

#ifndef CPP_COMPILING
}
#endif

/*
!contents -R2 -g -p -f -h

!define TEST_SYSTEM {slim}
!define TEST_RUNNER {/home/holz/etc/github/pwr-db/build/tests/useless_test_slim}
!define COMMAND_PATTERN {%m}
!define SLIM_VERSION {0.2}
!define SLIM_PORT {8099}
!define slim.timeout {100}

|Date_Conversion|
|epoch_date|epoch2date?|
|1578178800000|05.01.2020|
|1411213448658|20.09.2014|
|1411288848658|21.09.2014|
|1149626734000|06.06.2006|


|Date_Conversion|
|datestr|date2epoch?|
|05.01.2020|1578178800000|
|20.09.2014|1411167600000|
|21.09.2014|1411254000000|
|06.06.2006|1149548400000|

*/
