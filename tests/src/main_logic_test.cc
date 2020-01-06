#include "hldb.h"
#include "dbaccess/db_connection.h"
#include "dbaccess/db_defaults.h"
#include "dbaccess/date.h"

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <fmt/format.h>

using namespace std;
using namespace app::logic;
using namespace app::dbaccess;
using namespace app::dbaccess::defaults;


constexpr const char* DB_SCRIPT_INIT_PATH = "../dbinit/base_init.sql";
constexpr const char* DB_SCRIPT_DEP_PATH = "../dbinit/managers_dep_test.sql";
constexpr const char* DB_DATABASE_TEST = "biuro_podrozy_test";
class MainLogicTest : public ::testing::Test
{
protected:
   MainLogicTest()=default;
   virtual ~MainLogicTest()=default;
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
       FAIL() << "FAIL AT READING BASE FILE\n";
     }
     std::string query;
     while (std::getline(fs, query, ';'))
     {
       if (query ==""){
         continue;
       }
       hldb_inst.m_dbconn.query_res(query.c_str());
     }
   }
   hldb hldb_inst;
};

TEST_F(MainLogicTest, CostomerManagerTest)
{
  // hldb_inst.reserve_tour();
}
