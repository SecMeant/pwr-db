#include "hldb.h"
#include "dbaccess/date.h"

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <fmt/format.h>

using namespace std;
using namespace app::logic;
using namespace app::dbaccess;

constexpr const char* DB_SCRIPT_INIT_PATH = "../dbinit/base_init.sql";
constexpr const char* DB_SCRIPT_DEP_PATH = "../dbinit/managers_dep_test.sql";
constexpr const char* DB_DATABASE_TEST = "biuro_podrozy_test";
class DatabaseManagersTest : public ::testing::Test
{
protected:
   DatabaseManagersTest()=default;
   virtual ~DatabaseManagersTest()=default;
   void SetUp() override
   {
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
       if(hldb_inst.m_dbconn.query(query.c_str()) == false)
       {
        FAIL() << "FAIL AT QUERY\n" << query;
       }
     }
     fs.close();
     fs.open(DB_SCRIPT_DEP_PATH, std::fstream::in | std::fstream::out);

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
         FAIL() << "FAIL AT QUERY\n" << query;
       }
     }
   }
   hldb hldb_inst{DB_DATABASE_TEST};
};

TEST_F(DatabaseManagersTest, CostomerManagerTest){
  auto customers = hldb_inst.get_all_customers();
  EXPECT_EQ(customers.size(), 0)<< "INCORRECT CUSTOMERS COUNT";
  customer_t customer;
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
  customer.pesel ="444444444445";
  hldb_inst.add_customer(customer);
  customer.name ="Mario_4";
  customer.surname ="Bros_4";
  customer.email ="Mario_4.bros@op.pl";
  customer.pesel ="444444444446";
  hldb_inst.add_customer(customer);
  customers = hldb_inst.get_all_customers();
  EXPECT_EQ(customers.size(), 5)<< "INCORRECT CUSTOMERS COUNT";
  customer.name ="Mario_4";
  customer.surname ="Bros_4";
  customer.email ="Mario_47.bros@op.pl";
  customer.pesel ="444444444447";
  hldb_inst.add_customer(customer);
  app::sql::set_any(customer.pesel);
  app::sql::set_any(customer.email);
  customers = hldb_inst.get_customers_like(customer);
  ASSERT_EQ(customers.size(), 3)<< "INCORRECT CUSTOMERS COUNT";
  customer = customers[0];

  customer = hldb_inst.get_customers_like(customer.id);
  EXPECT_NE(customer.id, 0)<< "INCORRECT CUSTOMERS ID";
  hldb_inst.remove_customer(customer.id);
  customer = hldb_inst.get_customers_like(customer.id);
  EXPECT_EQ(customer.id, app::INVALID<int>)<< "INCORRECT CUSTOMERS COUNT";

  customer.name ="Mario_1";
  customer.surname ="Bros_1";
  app::sql::set_any(customer.email);
  app::sql::set_any(customer.pesel);
  customers = hldb_inst.get_customers_like(customer);

  customer.id = 1;
  customer.name ="Mario_M";
  customer.surname ="Bros_M";
  customer.email ="Mario_M.bros@op.pl";
  customer.pesel ="000000000000";
  hldb_inst.modify_customer(customer);
  customer = hldb_inst.get_customers_like(customer.id);
  EXPECT_EQ(customer.pesel, "000000000000")<< "INCORRECT CUSTOMERS PESEL";
}


TEST_F(DatabaseManagersTest, EmployeeManagerTest){
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
  employee.email ="worker_32.bros@op.pl";
  employee.phone_number ="297998993";
  hldb_inst.add_employee(employee);

  employee.name ="worker_3";
  employee.surname ="id_3";
  employee.hire_date =str2epoch("01.10.2013");
  employee.salary = 4000;
  employee.email ="worker_33.bros@op.pl";
  employee.phone_number ="397998993";
  hldb_inst.add_employee(employee);
  employees = hldb_inst.get_all_employees();
  EXPECT_EQ(employees.size(), 5)<< "INCORRECT employee COUNT";

  employee.name ="worker_3"; // search by name
  employee.surname ="id_3";// search by surname
  app::sql::set_any(employee.hire_date); //search param
  app::sql::set_any(employee.salary); // don't search by salary
  app::sql::set_any(employee.email); // dont search by salary
  app::sql::set_any(employee.phone_number);// dont search by salary

  employees = hldb_inst.get_employees_like(employee);
  EXPECT_EQ(employees.size(), 3)<< "INCORRECT employee COUNT";

  app::sql::set_any(employee.name); // don't search by name
  app::sql::set_any(employee.surname);// don't search by surname
  employee.hire_date =str2epoch("01.10.2013"); //search param
  app::sql::set_any(employee.salary); // don't search by salary
  app::sql::set_any(employee.email);// dont search by salary
  app::sql::set_any(employee.phone_number);// dont search by salary

  employees = hldb_inst.get_employees_like(employee);
  ASSERT_EQ(employees.size(), 2)<< "INCORRECT employee COUNT";

  employee = employees[0];
  employee = hldb_inst.get_employees_like(employee.id);
  EXPECT_NE(employee.id, 0)<< "INCORRECT employee ID";
  // remove employee with specified id
  employee.id = 4;
  hldb_inst.remove_employee(employee.id);
  employee = hldb_inst.get_employees_like(employee.id);
  EXPECT_EQ(employee.id, app::INVALID<int>)<< "INCORRECT employee COUNT";

  app::sql::set_any(employee.id);
  employee.name ="worker_1"; // search by name
  employee.surname ="id_1";// search by surname
  app::sql::set_any(employee.hire_date); //search param
  app::sql::set_any(employee.salary); // don't search by salary
  app::sql::set_any(employee.email);// dont search by salary
  app::sql::set_any(employee.phone_number);// dont search by salary
  employees = hldb_inst.get_employees_like(employee);
  ASSERT_NE(employees.size(), 0)<< "INCORRECT employee COUNT";
  employee = employees[0]; // get id from here
  // fill new data
  employee.name ="worker_1_mod";
  employee.surname ="id_1_mod";
  employee.hire_date =str2epoch("02.03.2011");
  employee.salary = 3500;
  employee.email ="worker_3.bros@op.pl";
  employee.phone_number ="997998993";
  // modify first worker
  hldb_inst.modify_employee(employee);
  employee = hldb_inst.get_employees_like(employee.id);
  EXPECT_EQ(epoch2str(employee.hire_date), "02.03.2011")<< "INCORRECT employee date";
}


TEST_F(DatabaseManagersTest, OfferManagerTest){
  auto offers = hldb_inst.get_all_offers();
  EXPECT_EQ(offers.size(), 0)<< "INCORRECT offerS COUNT";
  offer_t  offer;
  offer.name ="WONDERFUL TRIP1";
  offer.country ="POLAND";
  offer.city ="WROCLAW";
  offer.tickets_count = 50;
  offer.date_begin =str2epoch("01.10.2020");
  offer.date_end =str2epoch("02.11.2020");
  offer.price = 4000;
  offer.categoryid = 1;
  offer.insurance_cost =300;
  offer.extra_meals_cost =500;
  hldb_inst.add_offer(offer);

  offer.name ="WONDERFUL TRIP2";
  offer.country ="GERMANY";
  offer.city ="BERLIN";
  offer.tickets_count = 100;
  offer.date_begin =str2epoch("02.08.2020");
  offer.date_end =str2epoch("02.09.2020");
  offer.price = 4000;
  offer.categoryid = 1;
  offer.insurance_cost =300;
  offer.extra_meals_cost =500;
  hldb_inst.add_offer(offer);

  offer.name ="WONDERFUL TRIP3";
  offer.country ="UKRAINE";
  offer.city ="KIJOW";
  offer.tickets_count = 50;
  offer.date_begin =str2epoch("01.10.2023");
  offer.date_end =str2epoch("02.11.2023");
  offer.price = 4000;
  offer.categoryid = 1;
  offer.insurance_cost =300;
  offer.extra_meals_cost =500;
  hldb_inst.add_offer(offer);

  offer.name ="WONDERFUL TRIP3";
  offer.country ="UKRAINE";
  offer.city ="KIJOW";
  offer.tickets_count = 50;
  offer.date_begin =str2epoch("01.10.2021");
  offer.date_end =str2epoch("02.11.2021");
  offer.price = 4000;
  offer.categoryid = 1;
  offer.insurance_cost =300;
  offer.extra_meals_cost =500;
  hldb_inst.add_offer(offer);

  offer.name ="WONDERFUL TRIP3";
  offer.country ="UKRAINE";
  offer.city ="KIJOW";
  offer.tickets_count = 50;
  offer.date_begin =str2epoch("01.10.2021");
  offer.date_end =str2epoch("02.11.2021");
  offer.price = 4000;
  offer.categoryid = 1;
  offer.insurance_cost =300;
  offer.extra_meals_cost =500;
  hldb_inst.add_offer(offer);
  offers = hldb_inst.get_all_offers();
  EXPECT_EQ(offers.size(), 5)<< "INCORRECT offer COUNT";

  offer.name ="WONDERFUL TRIP3";
  offer.country ="UKRAINE";
  offer.city ="KIJOW";
  app::sql::set_any(offer.tickets_count);
  app::sql::set_any(offer.date_begin);
  app::sql::set_any(offer.date_end);
  app::sql::set_any(offer.price);
  app::sql::set_any(offer.categoryid);
  app::sql::set_any(offer.insurance_cost);
  app::sql::set_any(offer.extra_meals_cost);

  offers = hldb_inst.get_offers_like(offer);
  EXPECT_EQ(offers.size(), 3)<< "INCORRECT offer COUNT";

  app::sql::set_any(offer.name);
  app::sql::set_any(offer.country);
  app::sql::set_any(offer.city);
  app::sql::set_any(offer.tickets_count);
  app::sql::set_any(offer.date_end);
  app::sql::set_any(offer.price);
  app::sql::set_any(offer.categoryid);
  app::sql::set_any(offer.insurance_cost);
  app::sql::set_any(offer.extra_meals_cost);
  offer.date_begin = str2epoch("01.10.2021");

  offers = hldb_inst.get_offers_like(offer);
  ASSERT_EQ(offers.size(), 2)<< "INCORRECT offer COUNT";

  offer = offers[0];
  offer = hldb_inst.get_offers_like(offer.id);
  EXPECT_NE(offer.id, 0)<< "INCORRECT offer ID";

  // remove offer with specified id
  hldb_inst.remove_offer(offer.id);
  // check if offer has been deleted
  offer = hldb_inst.get_offers_like(offer.id);
  EXPECT_EQ(offer.id, app::INVALID<int>)<< "INCORRECT offer COUNT";


  offer.name ="WONDERFUL TRIP1";
  offer.country ="POLAND";
  offer.city ="WROCLAW";
  app::sql::set_any(offer.tickets_count);
  app::sql::set_any(offer.date_begin);
  app::sql::set_any(offer.date_end);
  app::sql::set_any(offer.price);
  app::sql::set_any(offer.categoryid);
  app::sql::set_any(offer.insurance_cost);
  app::sql::set_any(offer.extra_meals_cost);
  offers = hldb_inst.get_offers_like(offer);
  ASSERT_NE(offers.size(), 0)<< "INCORRECT offer COUNT";
  // modify first offer
  offer = offers[0];
  offer.name ="WONDERFUL_TRI213";
  offer.country ="GRENLAND";
  offer.city ="HMMMMMM";
  offer.tickets_count = 100;
  offer.date_begin =str2epoch("01.10.2025");
  offer.date_end =str2epoch("02.11.2025");
  offer.price = 300;
  offer.categoryid = 2;
  offer.insurance_cost =600;
  offer.extra_meals_cost =100;
  // // modify first worker
  hldb_inst.modify_offer(offer);
  offer = hldb_inst.get_offers_like(offer.id);
  EXPECT_EQ(epoch2str(offer.date_begin), "01.10.2025")<< "INCORRECT offer date";
  EXPECT_EQ(offer.name, "WONDERFUL_TRI213")<< "INCORRECT offer date";
}


TEST_F(DatabaseManagersTest, tourManagerTest){

  offer_t offer;
  offer.name ="WONDERFUL_TRIP1";
  offer.country ="UKRAINE";
  offer.city ="KIJOW";
  offer.tickets_count = 50;
  offer.date_begin =str2epoch("01.10.2021");
  offer.date_end =str2epoch("02.11.2021");
  offer.price = 4000;
  offer.categoryid = 1;
  offer.insurance_cost =300;
  offer.extra_meals_cost =500;
  hldb_inst.add_offer(offer);
  auto offers = hldb_inst.get_all_offers();
  ASSERT_EQ(offers.size(), 1)<< "INCORRECT offer COUNT";

  employee_t employee;
  employee.name ="worker_1";
  employee.surname ="id_1";
  employee.hire_date =str2epoch("01.10.2013");
  employee.salary = 4000;
  employee.email ="worker_1.bros@op.pl";
  employee.phone_number ="997998993";
  hldb_inst.add_employee(employee);
  auto employees = hldb_inst.get_all_employees();
  ASSERT_EQ(employees.size(), 1)<< "INCORRECT employee COUNT";

  customer_t customer;
  customer.name ="Mario_1";
  customer.surname ="Bros_1";
  customer.email ="Mario_1.bros@op.pl";
  customer.pesel ="111111111111";
  hldb_inst.add_customer(customer);
  auto customers = hldb_inst.get_all_customers();
  ASSERT_EQ(customers.size(), 1)<< "INCORRECT CUSTOMERS COUNT";

  auto tours = hldb_inst.get_all_tours();
  ASSERT_EQ(tours.size(), 0)<< "INCORRECT tourS COUNT";

  tour_t  tour;
  tour.debt =4000;
  tour.insurance = 0;
  tour.extra_meals =1;
  tour.state =static_cast<tour_state>(0);
  tour.reserved_tickets =6;
  tour.customersid = 1;
  tour.employeesid = 1;
  tour.offerid = 1;
  hldb_inst.add_tour(tour);

  tour.debt =6000;
  tour.insurance = 1;
  tour.extra_meals =0;
  tour.state =static_cast<tour_state>(0);
  tour.reserved_tickets =4;
  tour.customersid = 1;
  tour.employeesid = 1;
  tour.offerid = 1;
  hldb_inst.add_tour(tour);

  tour.debt =2000;
  tour.insurance = 1;
  tour.extra_meals =1;
  tour.state =static_cast<tour_state>(0);
  tour.reserved_tickets =5;
  tour.customersid = 1;
  tour.employeesid = 1;
  tour.offerid = 1;
  hldb_inst.add_tour(tour);

  tour.debt =2000;
  tour.insurance = 1;
  tour.extra_meals =1;
  tour.state =static_cast<tour_state>(0);
  tour.reserved_tickets =5;
  tour.customersid = 1;
  tour.employeesid = 1;
  tour.offerid = 1;
  hldb_inst.add_tour(tour);

  tour.debt =2000;
  tour.insurance = 1;
  tour.extra_meals =1;
  tour.state =static_cast<tour_state>(0);
  tour.reserved_tickets =5;
  tour.customersid = 1;
  tour.employeesid = 1;
  tour.offerid = 1;
  hldb_inst.add_tour(tour);
  tours = hldb_inst.get_all_tours();
  EXPECT_EQ(tours.size(), 5)<< "INCORRECT tour COUNT";

  app::sql::set_any(tour.insurance);
  app::sql::set_any(tour.extra_meals);
  app::sql::set_any(tour.state);
  app::sql::set_any(tour.customersid);
  app::sql::set_any(tour.employeesid);
  app::sql::set_any(tour.offerid);
  tour.debt =2000;
  tour.reserved_tickets =5;

  tours = hldb_inst.get_tours_like(tour);
  EXPECT_EQ(tours.size(), 3)<< "INCORRECT tour COUNT";

  tour = tours[0];
  tour = hldb_inst.get_tours_like(tour.id);
  EXPECT_NE(tour.id, 0)<< "INCORRECT tour ID";

  // remove tour with specified id
  tour.id = 4;
  hldb_inst.remove_tour(tour.id);
  // // check if tour has been deleted
  tour = hldb_inst.get_tours_like(tour.id);
  EXPECT_EQ(tour.id, app::INVALID<int>)<< "DELETING TOUR FAILED";

  app::sql::set_any(tour.id);
  app::sql::set_any(tour.insurance);
  app::sql::set_any(tour.extra_meals);
  app::sql::set_any(tour.state);
  app::sql::set_any(tour.customersid);
  app::sql::set_any(tour.employeesid);
  app::sql::set_any(tour.offerid);
  tour.debt =2000;
  tour.reserved_tickets =5;

  // modify first worker
  tour.id = 1;
  tour.debt =1234567;
  tour.insurance = 0;
  tour.extra_meals =1;
  tour.state = static_cast<tour_state>(0);
  tour.reserved_tickets =12;
  tour.customersid = 1;
  tour.employeesid = 1;
  tour.offerid = 1;
  hldb_inst.modify_tour(tour);
  tour = hldb_inst.get_tours_like(tour.id);
  EXPECT_EQ(tour.debt, 1234567)<< "INCORRECT tour debt";
  EXPECT_EQ(tour.reserved_tickets, 12)<< "INCORRECT tour tickets count";
}