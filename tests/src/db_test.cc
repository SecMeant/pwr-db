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
  ASSERT_EQ(customers.size(), 3)<< "INCORRECT CUSTOMERS COUNT";
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


TEST_F(HldbTest, EmployeeManagerTest){
  auto employees = hldb_inst.get_all_employees();
  EXPECT_EQ(employees.size(), 0)<< "INCORRECT EMPLOYEES COUNT";
  employee_t  employee;
  employee.name ="worker_1";
  employee.surname ="id_1";
  employee.hire_date =str2epoch("01.10.2000");
  employee.salary = 4000;
  employee.email ="worker1_1.bros@op.pl";
  employee.phone_number ="997998991";
  hldb_inst.add_employee(employee);

  employee.name ="worker_2";
  employee.surname ="id_2";
  employee.hire_date =str2epoch("01.10.2010");
  employee.salary = 4000;
  employee.email ="worker2_1.bros@op.pl";
  employee.phone_number ="997998992";
  hldb_inst.add_employee(employee);

  employee.name ="worker_3";
  employee.surname ="id_3";
  employee.hire_date =str2epoch("01.10.2015");
  employee.salary = 4000;
  employee.email ="worker_3.bros@op.pl";
  employee.phone_number ="997998993";
  hldb_inst.add_employee(employee);

  employee.name ="worker_3";
  employee.surname ="id_3";
  employee.hire_date =str2epoch("01.10.2013");
  employee.salary = 4000;
  employee.email ="worker_3.bros@op.pl";
  employee.phone_number ="997998993";
  hldb_inst.add_employee(employee);

  employee.name ="worker_3";
  employee.surname ="id_3";
  employee.hire_date =str2epoch("01.10.2013");
  employee.salary = 4000;
  employee.email ="worker_3.bros@op.pl";
  employee.phone_number ="997998993";
  hldb_inst.add_employee(employee);
  employees = hldb_inst.get_all_employees();
  EXPECT_EQ(employees.size(), 5)<< "INCORRECT employee COUNT";

  employee.name ="worker_3"; // search by name
  employee.surname ="id_3";// search by surname
  employee.hire_date =str2epoch(INVALID_DATE); //search param
  employee.salary = 0; // don't search by salary
  employee.email =""; // dont search by salary
  employee.phone_number ="";// dont search by salary

  employees = hldb_inst.get_employees_like(employee);
  EXPECT_EQ(employees.size(), 3)<< "INCORRECT employee COUNT";

  employee.name =""; // don't search by name
  employee.surname ="";// don't search by surname
  employee.hire_date =str2epoch("01.10.2013"); //search param
  employee.salary = 0; // don't search by salary
  employee.email ="";// dont search by salary
  employee.phone_number ="";// dont search by salary

  employees = hldb_inst.get_employees_like(employee);
  ASSERT_EQ(employees.size(), 2)<< "INCORRECT employee COUNT";

  employee = employees[0];
  employee = hldb_inst.get_employees_like(employee.id);
  EXPECT_NE(employee.id, 0)<< "INCORRECT employee ID";
  employee.id = 4;
  // remove employee with specified id
  hldb_inst.rmeove_employee(employee);
  employee.id = 3;
  employee.name ="worker_3"; // search by name
  employee.surname ="id_3";// search by surname
  employee.hire_date =str2epoch(INVALID_DATE); //search param
  employee.salary = 0; // don't search by salary
  employee.email =""; // dont search by salary
  employee.phone_number ="";// dont search by salary
  employees = hldb_inst.get_employees_like(employee);
  EXPECT_EQ(employees.size(), 2)<< "INCORRECT employee COUNT";

  employee.id = 0;
  employee.name ="worker_3"; // search by name
  employee.surname ="id_3";// search by surname
  employee.hire_date =str2epoch(INVALID_DATE); //search param
  employee.salary = 0; // don't search by salary
  employee.email =""; // dont search by salary
  employee.phone_number ="";// dont search by salary
  // don't look on id, remove all employees speified py params
  hldb_inst.rmeove_employee(employee);
  employees = hldb_inst.get_employees_like(employee);
  EXPECT_EQ(employees.size(), 0)<< "INCORRECT employee COUNT";

  employee.id = 1;
  employee.name ="worker_1";
  employee.surname ="id_1";
  employee.hire_date =str2epoch("02.03.2011");
  employee.salary = 3500;
  employee.email ="worker_3.bros@op.pl";
  employee.phone_number ="997998993";
  // modify first worker
  hldb_inst.modify_employee(employee);
  employee = hldb_inst.get_employees_like(employee.id);
  EXPECT_EQ(epoch2str(employee.hire_date), "02.03.2011")<< "INCORRECT employee date";
}