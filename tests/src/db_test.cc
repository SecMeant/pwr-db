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

TEST(DB_UTILS, dateConverterTest)
{
  string d_str = "05.01.20";
  uint64_t time_mill = 1578178800000;

  date_t base_date = date_t(Ms(time_mill));
  EXPECT_EQ(d_str, epoch2str(base_date));

  uint64_t time_conv = str2epoch(d_str.c_str(), "%d.%m.%y").time_since_epoch().count();
  EXPECT_EQ(time_mill, time_conv);
}


TEST_F(HldbTest, CostomerManagerTest){
  auto customers = hldb_inst.get_all_customers();
  EXPECT_EQ(customers.size(), 0)<< "INCORRECT CUSTOMERS COUNT";
  customer_t  customer;
  customer.name ="Mario_1";
  customer.surname ="Bros_1";
  customer.email ="Mario_1.bros@op.pl";
  customer.pesel ="111111111111";
  hldb_inst.add_customer(customer);
  customer.name ="Mario_2";
  customer.surname ="Bros_2";
  customer.email ="Mario_2.bros@op.pl";
  customer.pesel ="222222222222";
  hldb_inst.add_customer(customer);
  customer.name ="Mario_3";
  customer.surname ="Bros_3";
  customer.email ="Mario_3.bros@op.pl";
  customer.pesel ="333333333333";
  hldb_inst.add_customer(customer);
  customer.name ="Mario_4";
  customer.surname ="Bros_4";
  customer.email ="Mario_4.bros@op.pl";
  customer.pesel ="444444444444";
  hldb_inst.add_customer(customer);
  customers = hldb_inst.get_all_customers();
  EXPECT_EQ(customers.size(), 4)<< "INCORRECT CUSTOMERS COUNT";

  customer.name ="Mario_4";
  customer.surname ="Bros_4";
  customer.email ="Mario_4.bros@op.pl";
  customer.pesel ="444444444444";
  hldb_inst.add_customer(customer);
  customers = hldb_inst.get_all_customers();
  EXPECT_EQ(customers.size(), 5)<< "INCORRECT CUSTOMERS COUNT";
  customer.name ="Mario_4";
  customer.surname ="Bros_4";
  customer.email ="Mario_4.bros@op.pl";
  customer.pesel ="444444444444";
  hldb_inst.add_customer(customer);

  customers = hldb_inst.get_customers_like(customer);
  EXPECT_EQ(customers.size(), 3)<< "INCORRECT CUSTOMERS COUNT";
  customer = customers[0];

  customer = hldb_inst.get_customers_like(customer.id);
  EXPECT_NE(customer.id, 0)<< "INCORRECT CUSTOMERS ID";

  hldb_inst.rmeove_customer(customer);
  customers = hldb_inst.get_customers_like(customer);
  EXPECT_EQ(customers.size(), 2)<< "INCORRECT CUSTOMERS COUNT";

  customer.id = 0;
  hldb_inst.rmeove_customer(customer);
  customers = hldb_inst.get_customers_like(customer);
  EXPECT_EQ(customers.size(), 0)<< "INCORRECT CUSTOMERS COUNT";

  customer.id = 1;
  customer.name ="Mario_M";
  customer.surname ="Bros_M";
  customer.email ="Mario_M.bros@op.pl";
  customer.pesel ="000000000000";
  hldb_inst.modify_customer(customer);
  customer = hldb_inst.get_customers_like(customer.id);
  EXPECT_EQ(customer.pesel, "000000000000")<< "INCORRECT CUSTOMERS PESEL";
}


// TEST_F(HldbTest, EmployeeManagerTest){
//   auto customers = hldb_inst.get_all_customers();
//   EXPECT_EQ(customers.size(), 0)<< "INCORRECT CUSTOMERS COUNT";
//   employee_t  employee;
//   employee.name ="Mario_1";
//   employee.surname ="Bros_1";
//   employee.email ="Mario_1.bros@op.pl";
//   employee.pesel ="111111111111";
//   hldb_inst.add_employee(employee);
//   employee.name ="Mario_2";
//   employee.surname ="Bros_2";
//   employee.email ="Mario_2.bros@op.pl";
//   employee.pesel ="222222222222";
//   hldb_inst.add_employee(employee);
//   employee.name ="Mario_3";
//   employee.surname ="Bros_3";
//   employee.email ="Mario_3.bros@op.pl";
//   employee.pesel ="333333333333";
//   hldb_inst.add_employee(employee);
//   employee.name ="Mario_4";
//   employee.surname ="Bros_4";
//   employee.email ="Mario_4.bros@op.pl";
//   employee.pesel ="444444444444";
//   hldb_inst.add_employee(employee);
//   employees = hldb_inst.get_all_employees();
//   EXPECT_EQ(employees.size(), 4)<< "INCORRECT employeeS COUNT";

//   employee.name ="Mario_4";
//   employee.surname ="Bros_4";
//   employee.email ="Mario_4.bros@op.pl";
//   employee.pesel ="444444444444";
//   hldb_inst.add_employee(employee);
//   employees = hldb_inst.get_all_employees();
//   EXPECT_EQ(employees.size(), 5)<< "INCORRECT employeeS COUNT";
//   employee.name ="Mario_4";
//   employee.surname ="Bros_4";
//   employee.email ="Mario_4.bros@op.pl";
//   employee.pesel ="444444444444";
//   hldb_inst.add_employee(employee);

//   employees = hldb_inst.get_employees_like(employee);
//   EXPECT_EQ(employees.size(), 3)<< "INCORRECT employeeS COUNT";
//   employee = employees[0];

//   employee = hldb_inst.get_employees_like(employee.id);
//   EXPECT_NE(employee.id, 0)<< "INCORRECT employeeS ID";

//   hldb_inst.rmeove_employee(employee);
//   employees = hldb_inst.get_employees_like(employee);
//   EXPECT_EQ(employees.size(), 2)<< "INCORRECT employeeS COUNT";

//   employee.id = 0;
//   hldb_inst.rmeove_employee(employee);
//   employees = hldb_inst.get_employees_like(employee);
//   EXPECT_EQ(employees.size(), 0)<< "INCORRECT employeeS COUNT";

//   employee.id = 1;
//   employee.name ="Mario_M";
//   employee.surname ="Bros_M";
//   employee.email ="Mario_M.bros@op.pl";
//   employee.pesel ="000000000000";
//   hldb_inst.modify_employee(employee);
//   employee = hldb_inst.get_employees_like(employee.id);
//   EXPECT_EQ(employee.pesel, "000000000000")<< "INCORRECT CUSTOMERS PESEL";
// }