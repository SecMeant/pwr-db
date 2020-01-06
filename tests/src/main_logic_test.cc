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
constexpr const char* DB_SCRIPT_DEP_PATH = "../dbinit/logic_dep_test.sql";
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

     std::fstream fs(DB_SCRIPT_INIT_PATH, std::fstream::in);

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
       if(hldb_inst.m_dbconn.query(query.c_str()) == false)
       {
        // FAIL() << "FAIL AT QUERY\n" << query;
       }
     }
     fs.close();
     fs.open(DB_SCRIPT_DEP_PATH, std::fstream::in);

     if (!fs.is_open())
     {
       FAIL() << "FAIL AT READING DEP FILE\n";
     }
     while (std::getline(fs, query, ';'))
     {
       if (query ==""){
         continue;
       }
       if(hldb_inst.m_dbconn.query(query.c_str()) == false)
       {
        // FAIL() << "FAIL AT QUERY\n" << query;
       }
     }
   }
   hldb hldb_inst;
   std::string employee_log = "employee_1";
   std::string employee_pass = "a63ab36162a4f4ee6622ccd787b0a048c26b93acfc05c6b1843659b253c3c00b";
};

TEST_F(MainLogicTest, ReservationManager)
{
  customer_t customer;
  customer.name ="ardella";
  customer.surname ="reilly";
  customer.email ="areilly7@icio.us";
  app::sql::set_any(customer.pesel);
  app::sql::set_any(customer.id);
  auto c = hldb_inst.get_customers_like(customer);
  ASSERT_NE(c.size(),0) << "CUSTOMER NOT FOUND. SIZE: " << c.size();
  customer = c[0];
  ASSERT_TRUE(customer.valid());

  credentials_t cred;
  app::sql::set_any(cred.id);
  cred.login = employee_log;
  cred.pass_hash = employee_pass;
  hldb_inst.m_session.authenticate(cred);
  ASSERT_EQ(hldb_inst.m_session.state(),state_t::logedin);
}
