#include <gtest/gtest.h>
#include "hldb.h"
#include "dbaccess/db_connection.h"
#include "dbaccess/db_defaults.h"
using namespace app::logic;
using namespace app::dbaccess;
using namespace app::dbaccess::defaults;

class hdlbFixtrue : ::testing::Test
{
  hldb hldb_inst;
};

TEST(hdlbFixtrue, basicDatabaseConnection)
{
  db_connection c(
    DB_HOSTNAME, DB_DATABASE, DB_PORT_NO, { DB_USERNAME_HIPRIO, DB_PASSWORD_HIPRIO });
  EXPECT_EQ(true, c);

  c = db_connection(
    DB_HOSTNAME, DB_DATABASE, DB_PORT_NO, { DB_USERNAME_MIPRIO, DB_PASSWORD_MIPRIO });
  EXPECT_EQ(true, c);

  c = db_connection(
    DB_HOSTNAME, DB_DATABASE, DB_PORT_NO, { DB_USERNAME_LOPRIO, DB_PASSWORD_LOPRIO });
  EXPECT_EQ(true, c);

}

TEST(hdlbFixtrue, offerManagerTest){

  EXPECT_EQ(0, 0);
}
