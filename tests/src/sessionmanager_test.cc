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
class HldbTest : public ::testing::Test
{
protected:
  HldbTest()=default;
  virtual ~HldbTest()=default;

  std::vector<credentials_t>
  get_all_credentials()
  {
    constexpr auto query = "SELECT id, login, pass_hash, privilege, employeeid "
      "FROM biuro_podrozy_test.credentials";

    std::vector<credentials_t> ret;
    auto res = hldb_inst.m_dbconn.query_res(query);

    if (!res)
      return ret;

    for (auto i = 0ull; i < res->row_count; ++i) {
      auto row = mysql_fetch_row(res.get());
      credentials_t creds;
      creds.id = atoi(row[0]);
      creds.login = row[1];
      creds.pass_hash = row[2];
      creds.privilege = static_cast<privilege_level>(atoi(row[3]));
      creds.employeeid = atoi(row[4]);
      ret.push_back(std::move(creds));
    }

    return ret;
  }

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

    credentials = get_all_credentials();
  }

  hldb hldb_inst;
  std::vector<credentials_t> credentials;
};

TEST_F(HldbTest, SessionManagerTest) {
  ASSERT_TRUE(credentials.size() > 0);

  for (auto &cred : credentials) {
    EXPECT_TRUE(hldb_inst.m_session.authenticate(cred));
    EXPECT_EQ(hldb_inst.m_session.state(), state_t::logedin);
    EXPECT_EQ(hldb_inst.m_session.privilege(), cred.privilege);
  }
}
