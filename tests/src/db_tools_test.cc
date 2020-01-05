#include <gtest/gtest.h>
#include "hldb.h"
#include "dbaccess/db_connection.h"
#include "dbaccess/db_defaults.h"
#include "dbaccess/date.h"
#include <string>
using namespace std;
using namespace app::logic;
using namespace app::dbaccess;
using namespace app::dbaccess::defaults;


TEST(DB_TEST, basicDatabaseConnection)
{
  db_connection c(
    DB_HOSTNAME, DB_DATABASE, DB_PORT_NO, { DB_USERNAME_HIPRIO, DB_PASSWORD_HIPRIO });
  EXPECT_EQ(true, c)<< "HI_PRIO ACCOUNT INACCESSIBLE";

  c = db_connection(
    DB_HOSTNAME, DB_DATABASE, DB_PORT_NO, { DB_USERNAME_MIPRIO, DB_PASSWORD_MIPRIO });
  EXPECT_EQ(true, c)<< "MI_PRIO ACCOUNT INACCESSIBLE";

  c = db_connection(
    DB_HOSTNAME, DB_DATABASE, DB_PORT_NO, { DB_USERNAME_LOPRIO, DB_PASSWORD_LOPRIO });
  EXPECT_EQ(true, c)<< "LO_PRIO ACCOUNT INACCESSIBLE";
}

TEST(DB_UTILS, dateConverterTest)
{
  string d_str = "05.01.2020";
  uint64_t time_mill = 1578178800000;

  date_t base_date = date_t(tb(time_mill));
  EXPECT_EQ(d_str, epoch2str(base_date));

  uint64_t time_conv = str2epoch(d_str.c_str()).time_since_epoch().count();
  EXPECT_EQ(time_mill, time_conv);
  // first day in chrono life
  d_str = "01.01.1970";
  time_mill = 0;

  base_date = date_t(tb(time_mill));
  EXPECT_EQ(d_str, epoch2str(base_date));

  time_conv = str2epoch(d_str.c_str()).time_since_epoch().count();
  EXPECT_EQ(time_mill, time_conv);
}

