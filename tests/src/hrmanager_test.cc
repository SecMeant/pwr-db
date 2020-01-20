#include "hldb.h"
#include "dbaccess/db_connection.h"
#include "dbaccess/db_defaults.h"
#include "dbaccess/table/credentials.h"

#include <gtest/gtest.h>
#include <fstream>
#include <string>

using namespace std;
using namespace app::logic;
using namespace app::dbaccess;
using namespace app::dbaccess::defaults;


constexpr const char* DB_SCRIPT_INIT_PATH = "../dbinit/base_init.sql";
constexpr const char* DB_DEP_SCRIPT_INIT_PATH = "../dbinit/hrmanager_dep_test.sql";
constexpr const char* DB_DATABASE_TEST = "biuro_podrozy_test";
class HRManagerTest : public ::testing::Test
{
protected:
  HRManagerTest()=default;
  virtual ~HRManagerTest()=default;

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

    emps = hldb_inst.get_all_employees();
  }

  hldb hldb_inst;
  std::vector<employee_t> emps;
};

TEST_F(HRManagerTest, modify_salary_successed_with_positive_salary) {
  ASSERT_TRUE(emps.size() > 0);

  ASSERT_TRUE(hldb_inst.m_session.authenticate("manager_1", "passwd1"));

  for (auto &emp : emps) {
    auto old_salary = emp.salary;
    auto new_salary = old_salary * 2;

    EXPECT_TRUE(hldb_inst.m_hr.modify_salary(emp.id, new_salary));

    auto emp_renewed = hldb_inst.get_employees_like(emp.id);

    EXPECT_EQ(emp_renewed.salary, new_salary);
  }
}

TEST_F(HRManagerTest, modify_salary_fails_with_negative_salary) {
  ASSERT_TRUE(emps.size() > 0);

  ASSERT_TRUE(hldb_inst.m_session.authenticate("manager_1", "passwd1"));

  for (auto &emp : emps) {
    auto old_salary = emp.salary;
    auto new_salary = (old_salary + 1) * (-1);

    EXPECT_FALSE(hldb_inst.m_hr.modify_salary(emp.id, new_salary));

    auto emp_renewed = hldb_inst.get_employees_like(emp.id);

    EXPECT_EQ(emp_renewed.salary, old_salary);
  }
}

TEST_F(HRManagerTest, ModifySalaryDenyTest) {
  ASSERT_TRUE(emps.size() > 0);

  ASSERT_TRUE(hldb_inst.m_session.authenticate("employee_1", "passwd2"));

  for (auto &emp : emps) {
    auto old_salary = emp.salary;
    auto new_salary = old_salary * 2;

    EXPECT_FALSE(hldb_inst.m_hr.modify_salary(emp.id, new_salary));

    auto emp_renewed = hldb_inst.get_employees_like(emp.id);

    EXPECT_NE(emp_renewed.salary, new_salary);
  }
}

TEST_F(HRManagerTest, PromoteTest) {
  ASSERT_TRUE(emps.size() > 0);
  ASSERT_TRUE(hldb_inst.m_session.authenticate("manager_1", "passwd1"));

  for (auto &emp : emps) {
    constexpr auto new_privilege = privilege_level::high;

    EXPECT_TRUE(hldb_inst.m_hr.promote(emp.id, new_privilege));

    credentials_t creds;
    app::sql::set_any(creds.id);
    creds.employeeid = emp.id;
    app::sql::set_any(creds.login);
    app::sql::set_any(creds.pass_hash);
    app::sql::set_any(creds.privilege);

    auto vcreds = hldb_inst.get_credentials_like(creds);

    auto row_cnt = vcreds.size();
    EXPECT_TRUE(row_cnt == 1);

    if (row_cnt != 1)
      continue;

    creds = vcreds[0];

    EXPECT_TRUE(creds.valid());

    EXPECT_EQ(creds.privilege, new_privilege);
  }
}
