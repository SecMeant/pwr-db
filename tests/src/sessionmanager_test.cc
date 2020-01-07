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


const char* DB_SCRIPT_INIT_PATH = "../dbinit/base_init.sql";
const char* DB_DEP_SCRIPT_INIT_PATH = "../dbinit/sessionmanager_dep_test.sql";
const char* DB_DATABASE_TEST = "biuro_podrozy_test";
class SessionManagerTest : public ::testing::Test
{
protected:
  SessionManagerTest()=default;
  virtual ~SessionManagerTest()=default;

  struct creds
  {
    std::string_view username, password;
    privilege_level priv;
  };

  void
  execute_sql(const char * filename)
  {
    std::ifstream fs(filename, std::fstream::in);

    if (!fs.is_open())
    {
      FAIL() << "FAIL AT READING FILE\n";
    }
    std::string query;
    while (std::getline(fs, query, ';'))
    {
      if (query ==""){
        continue;
      }
      hldb_inst.m_dbconn.query(query.c_str());
    }
  }

  void SetUp() override
  {
    hldb_inst.m_dbconn = db_connection(
        DB_HOSTNAME, DB_DATABASE_TEST, DB_PORT_NO, { DB_USERNAME, DB_PASSWORD});
    if(!hldb_inst.m_dbconn)
    {
      FAIL() << "CAN\'T CONNECT AS SUPERUSER\n";
    }

    execute_sql(DB_SCRIPT_INIT_PATH);
    execute_sql(DB_DEP_SCRIPT_INIT_PATH);

    credentials = {
      {"mamanger_1", "passwd1", privilege_level::high},
      {"employee_1", "passwd2", privilege_level::mid},
      {"employee_2", "passwd3", privilege_level::mid},
      {"employee_3", "passwd4", privilege_level::mid}
    };
  }

  hldb hldb_inst;
  std::vector<creds> credentials;
};

TEST_F(SessionManagerTest, AuthTest) {
  ASSERT_TRUE(credentials.size() > 0);

  for (auto &cred : credentials) {
    EXPECT_TRUE(hldb_inst.m_session.authenticate(cred.username, cred.password));
    EXPECT_EQ(hldb_inst.m_session.state(), state_t::logedin);
    EXPECT_EQ(hldb_inst.m_session.privilege(), cred.priv);
  }

  EXPECT_FALSE(hldb_inst.m_session.authenticate("asdf", "qwer"));
  EXPECT_EQ(hldb_inst.m_session.state(), state_t::logedout);

  auto &cred = credentials[0];
  EXPECT_TRUE(hldb_inst.m_session.authenticate(cred.username, cred.password));
  EXPECT_EQ(hldb_inst.m_session.state(), state_t::logedin);
  EXPECT_EQ(hldb_inst.m_session.privilege(), cred.priv);
}
