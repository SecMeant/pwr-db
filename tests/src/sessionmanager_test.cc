#include "dbaccess/date.h"
#include "hldb.h"
#include "hldb_mock.h"
#include "dbaccess/db_defaults.h"

#include <fmt/format.h>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace app;
using namespace app::logic;
using namespace app::dbaccess;
using namespace testing;


const char *DB_SCRIPT_INIT_PATH = "../dbinit/base_init.sql";
const char *DB_DEP_SCRIPT_INIT_PATH = "../dbinit/sessionmanager_dep_test.sql";
const char *DB_DATABASE_TEST = "biuro_podrozy_test";

class SessionManagerTest : public ::testing::Test
{
protected:
  SessionManagerTest() = default;
  virtual ~SessionManagerTest() = default;

  bool
  check_creds(std::string_view u, std::string_view p)
  {
    auto it = std::find_if(
      std::begin(credentials), std::end(credentials), [&](const auto &c) {
        return c.login == u && c.pass_hash == hash_mock(p);
      });

    return it != std::end(credentials);
  }

  std::vector<credentials_t>
  get_credentials_like_mock(const credentials_t &creds)
  {
    std::vector<credentials_t> ret;

    for (auto &c : this->credentials) {
        if (
            (sql::any(creds.id)         || c.id == creds.id)
        &&  (sql::any(creds.employeeid) || c.employeeid == creds.employeeid)
        &&  (sql::any(creds.login)      || c.login == creds.login)
        &&  (sql::any(creds.pass_hash)  || c.pass_hash == creds.pass_hash)
        &&  (sql::any(creds.privilege)  || c.privilege == creds.privilege)
        ) ret.push_back(c);
    }

    return ret;
  }

  static std::string
  hash_mock(const std::string_view s)
  {
    auto ret = std::string(s);
    ret += "passhash";
    return ret;
  }

  static employee_t
  get_employees_like_mock(int id)
  {
    employee_t random_employee;
    random_employee.id = 1234;
    random_employee.name = "asdf";
    random_employee.surname = "qwer";
    random_employee.hire_date = str2epoch("11.11.2011");
    random_employee.salary = 1337;
    random_employee.email = "asdf@qwer.com";
    random_employee.phone_number = "123456789";
    return random_employee;
  }

  void
  SetUp() override
  {
    credentials_t c;

    c.id = 1;
    c.employeeid = 2;
    c.login = "manager1";
    c.pass_hash = hash_mock(c.login);
    c.privilege = privilege_level::high;

    credentials.push_back(std::move(c));

    c.id = 2;
    c.employeeid = 3;
    c.login = "employee1";
    c.pass_hash = hash_mock(c.login);
    c.privilege = privilege_level::mid;

    credentials.push_back(std::move(c));

    c.id = 3;
    c.employeeid = 4;
    c.login = "employee2";
    c.pass_hash = hash_mock(c.login);
    c.privilege = privilege_level::mid;

    credentials.push_back(std::move(c));

    c.id = 4;
    c.employeeid = 5;
    c.login = "employee3";
    c.pass_hash = hash_mock(c.login);
    c.privilege = privilege_level::mid;

    credentials.push_back(std::move(c));

    c.id = 5;
    c.employeeid = 6;
    c.login = defaults::DB_USERNAME_HIPRIO;
    c.pass_hash = hash_mock(defaults::DB_PASSWORD_HIPRIO);
    c.privilege = privilege_level::high;

    credentials.push_back(std::move(c));

    c.id = 6;
    c.employeeid = 7;
    c.login = defaults::DB_USERNAME_MIPRIO;
    c.pass_hash = hash_mock(defaults::DB_PASSWORD_MIPRIO);
    c.privilege = privilege_level::mid;

    credentials.push_back(std::move(c));

    c.id = 7;
    c.employeeid = 8;
    c.login = defaults::DB_USERNAME_LOPRIO;
    c.pass_hash = hash_mock(defaults::DB_PASSWORD_LOPRIO);
    c.privilege = privilege_level::low;

    credentials.push_back(std::move(c));

    invalid_credentials.username = "somebadusername";
    invalid_credentials.password = "somebadpassword";

    login_info_t li;

    li.username = "manager1";
    li.password = li.username;
    li.priv = privilege_level::high;

    login_info.push_back(li);

    li.username = "employee1";
    li.password = li.username;
    li.priv = privilege_level::mid;

    login_info.push_back(li);

    li.username = "employee2";
    li.password = li.username;
    li.priv = privilege_level::mid;

    login_info.push_back(li);

    li.username = "employee3";
    li.password = li.username;
    li.priv = privilege_level::mid;

    login_info.push_back(li);

  }
  
  struct login_info_t
  {
    std::string username, password;
    privilege_level priv;
  };

  std::vector<credentials_t> credentials;
  std::vector<login_info_t> login_info;
  login_info_t invalid_credentials;
};

TEST_F(SessionManagerTest, authenticate_Updates_Login_Status_On_Success)
{
  ASSERT_TRUE(credentials.size() > 0);

  hldb_mock hm(DB_DATABASE_TEST);
  session_manager sm(hm);

  ON_CALL(hm, authenticate).WillByDefault(
    Invoke([&](auto &&... Args) -> bool { return check_creds(Args...); }));

  EXPECT_CALL(hm, authenticate(_, _))
    .Times(AnyNumber());


  ON_CALL(hm, get_credentials_like(An<const credentials_t &>()))
    .WillByDefault(Invoke([&](auto &&... Args) -> auto {
      return get_credentials_like_mock(Args...);
    }));

  EXPECT_CALL(hm, get_credentials_like(An<const credentials_t &>()))
    .Times(AnyNumber());


  ON_CALL(hm, hash)
    .WillByDefault(Invoke([&](auto&& arg) -> auto { return hash_mock(arg); }));

  EXPECT_CALL(hm, hash)
    .Times(AnyNumber());


  ON_CALL(hm, get_employees_like(An<int>()))
    .WillByDefault(Invoke(get_employees_like_mock));

  EXPECT_CALL(hm, get_employees_like(An<int>()))
    .Times(AnyNumber());


  for (auto &li : login_info) {
    ASSERT_TRUE(sm.authenticate(li.username, li.password));
    ASSERT_EQ(sm.state(), state_t::logedin);
    ASSERT_EQ(sm.privilege(), li.priv);
  }
}

TEST_F(SessionManagerTest, authenticate_Updates_Login_Status_On_Failre)
{
  ASSERT_TRUE(credentials.size() > 0);

  hldb_mock hm(DB_DATABASE_TEST);
  session_manager sm(hm);

  ON_CALL(hm, authenticate).WillByDefault(
    Invoke([&](auto &&... Args) -> bool { return check_creds(Args...); }));

  EXPECT_CALL(hm, authenticate(_, _))
    .Times(AnyNumber());


  ON_CALL(hm, get_credentials_like(An<const credentials_t &>()))
    .WillByDefault(Invoke([&](auto &&... Args) -> auto {
      return get_credentials_like_mock(Args...);
    }));

  EXPECT_CALL(hm, get_credentials_like(An<const credentials_t &>()))
    .Times(AnyNumber());


  ON_CALL(hm, hash)
    .WillByDefault(Invoke([&](auto&& arg) -> auto { return hash_mock(arg); }));

  EXPECT_CALL(hm, hash)
    .Times(AnyNumber());


  ON_CALL(hm, get_employees_like(An<int>()))
    .WillByDefault(Invoke(get_employees_like_mock));

  EXPECT_CALL(hm, get_employees_like(An<int>()))
    .Times(AnyNumber());

  ASSERT_FALSE(sm.authenticate(invalid_credentials.username,
                               invalid_credentials.password));

  ASSERT_EQ(sm.state(), state_t::logedout);
}
