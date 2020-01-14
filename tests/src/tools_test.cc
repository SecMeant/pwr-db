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

class test_time_utils : public ::testing::Test
{
public:
  test_time_utils() = default;
  virtual ~test_time_utils()= default;
   void
  SetUp() override
  {
    date_from_current_age_str = "05.01.2020";
    date_from_current_age_ms = 1578178800000;
    fisrt_valid_date_str = "01.01.1970";
    fisrt_valid_date_ms = 0;
    incorrect_date_str = "01.01.197@";
    incorrect_date_ms = -1;
  }

  string date_from_current_age_str;
  uint64_t date_from_current_age_ms;
  string fisrt_valid_date_str;
  uint64_t fisrt_valid_date_ms;
  string incorrect_date_str;
  uint64_t incorrect_date_ms;
};

TEST_F(test_time_utils, date_convertion_test)
{
  date_t base_date = date_t(tb(date_from_current_age_ms));
  ASSERT_EQ(date_from_current_age_str, epoch2str(base_date));

  uint64_t time_conv = str2epoch(date_from_current_age_str.c_str()).time_since_epoch().count();
  ASSERT_EQ(date_from_current_age_ms, time_conv);
  // first day in chrono life

  base_date = date_t(tb(fisrt_valid_date_ms));
  ASSERT_EQ(fisrt_valid_date_str, epoch2str(base_date));

  time_conv = str2epoch(fisrt_valid_date_str.c_str()).time_since_epoch().count();
  ASSERT_EQ(fisrt_valid_date_ms, time_conv);

  // VERIFY WRONG DATA
  base_date = date_t(tb(incorrect_date_ms));
  ASSERT_NE(incorrect_date_str, epoch2str(base_date));

  time_conv = str2epoch(incorrect_date_str.c_str()).time_since_epoch().count();
  ASSERT_EQ(incorrect_date_ms, time_conv);
}

