#include <gtest/gtest.h>
#include "hldb.h"
#include "dbaccess/db_connection.h"
#include "dbaccess/db_defaults.h"
#include <fstream>
#include <string>
#include <fmt/format.h>

using namespace std;
using namespace app::logic;
using namespace app::dbaccess;
using namespace app::dbaccess::defaults;

constexpr const char* DB_SCRIPT_INIT_PATH = "../dbinit/test_init.sql";
constexpr const char* DB_DATABASE_TEST = "biuro_podrozy_test";
class HldbTest : public ::testing::Test
{
protected:
   HldbTest()=default;
   virtual ~HldbTest()=default;
   void SetUp() override
   {
     hldb_inst.m_dbconn = db_connection(
       DB_HOSTNAME, DB_DATABASE_TEST, DB_PORT_NO, { DB_USERNAME, DB_PASSWORD });
     if(!hldb_inst.m_dbconn)
     {
        FAIL() << "CAN\'T CONNECT AS SUPERUSER\n";
     }

     std::fstream fs(DB_SCRIPT_INIT_PATH, std::fstream::in | std::fstream::out);

     if (!fs.is_open())
     {
       FAIL() << "FAIL AT READING FILE\n";
     }
     std::string line;
     while (std::getline(fs, line, ';'))
     {
      if (line ==""){
        continue;
      }
      hldb_inst.m_dbconn.query_res(line.c_str());
     }
   }

   hldb hldb_inst;

};

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

TEST_F(HldbTest, CostomerManagerTest){
  EXPECT_EQ(0,0);
}
