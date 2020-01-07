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
        FAIL() << "FAIL AT QUERY\n" << query;
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
       if (query =="" || query == "\n"){
         continue;
       }
       if(hldb_inst.m_dbconn.query(query.c_str()) == false)
       {
        FAIL() << "FAIL AT QUERY\n" << query;
       }
     }
   }
   hldb hldb_inst;
   std::string employee_log = "employee_1";
   std::string employee_pass = "alamakota";
};

TEST_F(MainLogicTest, ReservationManagerReserve)
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

  offer_t offer;
  offer.country ="japonia";
  offer.city ="tokio";
  app::sql::set_any(offer.name);
  app::sql::set_any(offer.id);
  app::sql::set_any(offer.tickets_count);
  app::sql::set_any(offer.date_begin);
  app::sql::set_any(offer.date_end);
  app::sql::set_any(offer.price);
  app::sql::set_any(offer.categoryid);
  app::sql::set_any(offer.insurance_cost);
  app::sql::set_any(offer.extra_meals_cost);

  auto o = hldb_inst.get_offers_like(offer);
  ASSERT_NE(o.size(), 0)<< "INCORRECT offer COUNT";
  offer = o[0];
  ASSERT_TRUE(offer.valid());

  hldb_inst.m_session.authenticate(employee_log, employee_pass);
  ASSERT_EQ(hldb_inst.m_session.state(),state_t::logedin);

  int tickets_count =10;
  int tc_copy = offer.tickets_count;
  hldb_inst.res_manager.reserve_tour(offer.id,customer.id,tickets_count,0,1);
  tour_t tour;
  app::sql::set_any(tour.id);
  app::sql::set_any(tour.state);
  app::sql::set_any(tour.employeesid);
  app::sql::set_any(tour.debt);
  tour.extra_meals = 1;
  tour.insurance = 0;
  tour.customersid = customer.id;
  tour.offerid = offer.id;
  tour.reserved_tickets =tickets_count;
  auto tours = hldb_inst.get_tours_like(tour);
  ASSERT_GE(tours.size(), 1)<< "Tour hasn't been reserved";
  offer = hldb_inst.get_offers_like(offer.id);
  EXPECT_EQ(offer.tickets_count+tickets_count,tc_copy) << "Offer has incorrect ticket number";
  // reserve 5 more tickets
  tickets_count = 15;
  tour = tours[0];
  tour.reserved_tickets = tickets_count;
  hldb_inst.res_manager.modify(tour);
  offer = hldb_inst.get_offers_like(offer.id);
  EXPECT_EQ(offer.tickets_count+tickets_count,tc_copy) << "Offer has incorrect ticket number";
  // resign from 10 tickets
  tickets_count = 5;
  tour = tours[0];
  tour.reserved_tickets = tickets_count;
  hldb_inst.res_manager.modify(tour);
  offer = hldb_inst.get_offers_like(offer.id);
  EXPECT_EQ(offer.tickets_count+tickets_count,tc_copy) << "Offer has incorrect ticket number";

  hldb_inst.res_manager.resign(tour.id);
  offer = hldb_inst.get_offers_like(offer.id);
  EXPECT_EQ(offer.tickets_count,tc_copy) << "Offer has incorrect ticket number";
}
