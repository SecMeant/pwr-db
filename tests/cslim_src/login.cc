extern "C"
{
#include <CSlim/Fixtures.h>
#include <CSlim/SlimList.h>
#include <CSlim/compatibility.h>
}

#include "hldb.h"
#include "dbaccess/db_defaults.h"

using namespace app::logic;

#ifndef CPP_COMPILING
extern "C" {
#endif

struct login_info
{
  std::string login, password;
  app::logic::hldb_i *hldb;
  char result[32];
};

static const char *
set_Login(void *void_self, SlimList *args)
{
  login_info *self = (login_info *)void_self;
  self->login = SlimList_GetStringAt(args, 0);
  return self->result;
}

static const char *
set_Password(void *void_self, SlimList *args)
{
  login_info *self = (login_info *)void_self;
  self->password = SlimList_GetStringAt(args, 0);
  return self->result;
}

static const char *
login(void *void_self, SlimList *args)
{
  login_info *self = (login_info *)void_self;
  auto status = self->hldb->login(self->login, self->password);
  return status ? "Success" : "Failed";
}

void* Login_Create(StatementExecutor* errorHandler, SlimList* args)
{
  login_info* self = new login_info();
  self->hldb = new hldb(app::dbaccess::defaults::DB_DATABASE);
  self->result[0] = 0;
  return self;
}

void Login_Destroy(void* void_self)
{
  login_info* self = (login_info*)void_self;
  delete self->hldb;
  delete self;
}

SLIM_CREATE_FIXTURE(Login)
SLIM_FUNCTION(set_Login);
SLIM_FUNCTION(set_Password);
SLIM_FUNCTION(login);
SLIM_END

#ifndef CPP_COMPILING
}
#endif

/*
!contents -R2 -g -p -f -h

!define TEST_SYSTEM {slim}
!define TEST_RUNNER {/home/holz/etc/github/pwr-db/build/tests/useless_test_slim}
!define COMMAND_PATTERN {%m}
!define SLIM_VERSION {0.2}
!define SLIM_PORT {8099}
!define slim.timeout {100}

|Login|
|login|password|login?|
|manager_1|passwd1|Success|
|employee_1|passwd2|Success|
|employee_2|passwd3|Success|
|employee_3|passwd4|Success|
|somebadlogin|somebadpasswd|Failed|

*/
