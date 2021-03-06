#include "dbaccess/date.h"
#include "hldb.h"
#include "hldb_mock.h"

#include <fmt/format.h>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace app::logic;
using namespace app::dbaccess;
using namespace testing;
using testing::_;

constexpr const char *DB_SCRIPT_INIT_PATH = "../dbinit/base_init.sql";
constexpr const char *DB_SCRIPT_DEP_PATH = "../dbinit/reservation_dep_test.sql";
constexpr const char *DB_DATABASE_TEST = "biuro_podrozy_test";
class ReservationManagerTest : public ::testing::Test
{
protected:
  ReservationManagerTest() = default;
  virtual ~ReservationManagerTest() = default;
  void
  SetUp() override
  {
    if (!hldb_inst.m_dbconn) {
      FAIL() << "CAN\'T CONNECT AS SUPERUSER\n";
    }

    std::fstream fs(DB_SCRIPT_INIT_PATH, std::fstream::in);

    if (!fs.is_open()) {
      FAIL() << "FAIL AT READING BASE FILE\n";
    }
    std::string query;
    while (std::getline(fs, query, ';')) {
      if (query == "") {
        continue;
      }
      if (hldb_inst.m_dbconn.query(query.c_str()) == false) {
        FAIL() << "FAIL AT QUERY\n" << query;
      }
    }
    fs.close();
    fs.open(DB_SCRIPT_DEP_PATH, std::fstream::in);

    if (!fs.is_open()) {
      FAIL() << "FAIL AT READING DEP FILE\n";
    }
    while (std::getline(fs, query, ';')) {
      if (query == "" || query == "\n") {
        continue;
      }
      if (hldb_inst.m_dbconn.query(query.c_str()) == false) {
        FAIL() << "FAIL AT QUERY\n" << query;
      }
    }

    offer_t o;
    o.id = 1;
    o.name = "Wycieczka do japonii";
    o.country = "Japonia";
    o.city = "Shibuya";
    o.date_begin = str2epoch("12.03.2015");
    o.date_end = str2epoch("23.04.2016");
    o.price = 1337;
    o.insurance_cost = 1234;
    o.extra_meals_cost = 4567;
    o.categoryid = 2;
    o.tickets_count = 13;

    offers.push_back(std::move(o));

    customer_t c;
    c.id = 1;
    c.name = "Jan";
    c.surname = "Kowalski";
    c.email = "JanKowalski@wp.pl";
    c.pesel = "12345678987";

    customers.push_back(std::move(c));

    employee_t e;
    e.id = 1;
    e.name = "Kamil";
    e.surname = "Rutkowski";
    e.hire_date = str2epoch("11.11.2018");
    e.salary = 1345;
    e.email = "KamilRutkowski@wp.pl";
    e.phone_number = "123456789";

    employees.push_back(std::move(e));
  }

  hldb hldb_inst{ DB_DATABASE_TEST };
  std::string employee_log = "employee_1";
  std::string employee_pass = "alamakota";
  std::vector<offer_t> offers;
  std::vector<customer_t> customers;
  std::vector<employee_t> employees;
};

TEST_F(ReservationManagerTest, add_tour_Properly_Fills_Tour_Structure_With_Customer_And_Employee_Information)
{
  ASSERT_TRUE(offers.size() > 0);
  ASSERT_TRUE(customers.size() > 0);
  ASSERT_TRUE(employees.size() > 0);

  hldb_mock hm(DB_DATABASE_TEST);
  reservation_manager rm(hm);
  auto of = offers[0];
  EXPECT_CALL(hm, get_offers_like(of.id))
    .Times(1)
    .WillOnce(Return(of));

  auto cu = customers[0];
  EXPECT_CALL(hm, get_customers_like(cu.id))
    .Times(1)
    .WillOnce(Return(cu));

  auto emp = employees[0];
  EXPECT_CALL(hm, get_logged_user())
    .Times(1)
    .WillOnce(ReturnRef(emp));

  tour_t tour;
  ON_CALL(hm, add_tour)
    .WillByDefault(Invoke([&tour](const tour_t &t) -> bool {
      tour = t;
      return t.valid();
    }));

  EXPECT_CALL(hm, add_tour)
    .Times(1);

  int ticket_count = 10;
  bool insurance = false;
  bool extra_meals = true;
  int debt = ticket_count * (of.price + of.extra_meals_cost);
  ASSERT_TRUE(rm.reserve_tour(of.id, cu.id, ticket_count, insurance, extra_meals));
  ASSERT_TRUE(tour.offerid == of.id);
  ASSERT_TRUE(tour.customersid == cu.id);
  ASSERT_TRUE(tour.employeesid == emp.id);
  ASSERT_TRUE(tour.reserved_tickets == ticket_count);
  ASSERT_TRUE(tour.insurance == insurance);
  ASSERT_TRUE(tour.extra_meals == extra_meals);
  ASSERT_TRUE(tour.debt == debt);
}

TEST_F(ReservationManagerTest, ReservationManagerReserve)
{
  customer_t customer;
  customer.name = "ardella";
  customer.surname = "reilly";
  customer.email = "areilly7@icio.us";
  app::sql::set_any(customer.pesel);
  app::sql::set_any(customer.id);
  auto c = hldb_inst.get_customers_like(customer);
  ASSERT_NE(c.size(), 0) << "CUSTOMER NOT FOUND. SIZE: " << c.size();
  customer = c[0];
  ASSERT_TRUE(customer.valid());

  offer_t offer;
  offer.country = "japonia";
  offer.city = "tokio";
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
  ASSERT_NE(o.size(), 0) << "INCORRECT offer COUNT";
  offer = o[0];
  ASSERT_TRUE(offer.valid());

  hldb_inst.m_session.authenticate(employee_log, employee_pass);
  ASSERT_EQ(hldb_inst.m_session.state(), state_t::logedin);

  int tickets_count = 10;
  int tc_copy = offer.tickets_count;
  hldb_inst.make_reservation(offer.id, customer.id, tickets_count, 0, 1);
  tour_t tour;
  app::sql::set_any(tour.id);
  app::sql::set_any(tour.state);
  app::sql::set_any(tour.employeesid);
  app::sql::set_any(tour.debt);
  tour.extra_meals = 1;
  tour.insurance = 0;
  tour.customersid = customer.id;
  tour.offerid = offer.id;
  tour.reserved_tickets = tickets_count;
  auto tours = hldb_inst.get_tours_like(tour);
  ASSERT_GE(tours.size(), 1) << "Tour hasn't been reserved";
  offer = hldb_inst.get_offers_like(offer.id);
  EXPECT_EQ(offer.tickets_count + tickets_count, tc_copy)
    << "Offer has incorrect ticket number";
  // reserve 5 more tickets
  tickets_count = 15;
  tour = tours[0];
  tour.reserved_tickets = tickets_count;
  hldb_inst.modify_reservation(tour);
  offer = hldb_inst.get_offers_like(offer.id);
  EXPECT_EQ(offer.tickets_count + tickets_count, tc_copy)
    << "Offer has incorrect ticket number";
  // resign from 10 tickets
  tickets_count = 5;
  tour = tours[0];
  tour.reserved_tickets = tickets_count;
  hldb_inst.modify_reservation(tour);
  offer = hldb_inst.get_offers_like(offer.id);
  EXPECT_EQ(offer.tickets_count + tickets_count, tc_copy)
    << "Offer has incorrect ticket number";

  hldb_inst.drop_reservation(tour.id);
  offer = hldb_inst.get_offers_like(offer.id);
  EXPECT_EQ(offer.tickets_count, tc_copy)
    << "Offer has incorrect ticket number";
}
