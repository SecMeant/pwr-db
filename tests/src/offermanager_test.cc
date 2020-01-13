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
using ::testing::Invoke;

constexpr const char *DB_SCRIPT_INIT_PATH = "../dbinit/base_init.sql";
constexpr const char *DB_SCRIPT_DEP_PATH = "../dbinit/offer_dep_test.sql";
constexpr const char *DB_DATABASE_TEST = "biuro_podrozy_test";
class OfferManagerTest : public ::testing::Test
{
protected:
  OfferManagerTest() = default;
  virtual ~OfferManagerTest() = default;
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

    offers = hldb_inst.get_all_offers();
    tours = hldb_inst.get_all_tours();
  }

  hldb hldb_inst{ DB_DATABASE_TEST };
  std::string employee_log = "employee_1";
  std::string employee_pass = "alamakota";
  std::vector<offer_t> offers;
  std::vector<tour_t> tours;
};

TEST_F(OfferManagerTest, OfferManagerModify)
{

  ASSERT_TRUE(offers.size() > 0);
  ASSERT_TRUE(tours.size() > 0);

  std::vector<offer_t> selected_offers;
  std::copy_if(offers.begin(), offers.end(),std::back_inserter(selected_offers),[](offer_t &o){ if (o.tickets_count == 55) return true; else return false; });

  hldb_mock hm("ghjk");
  offer_manager rm(hm);

  auto old_off = selected_offers[0];
  EXPECT_CALL(hm, get_offers_like(old_off))
    .Times(0)
    .WillOnce(Return(selected_offers));

  offer_t new_off = old_off;
  int price = 1500;
  int insurance_cost = 400;
  int extra_meals_cost = 200;
  new_off.price = price;
  new_off.insurance_cost = insurance_cost;
  new_off.extra_meals_cost = extra_meals_cost;

  tour_t tour;
  EXPECT_CALL(hm, modify_tour).WillRepeatedly(Return([](tour_t& t){

    fmt::print("CAPTURED: {} \n", t.debt);
    // ASSERT_TRUE(tour.offerid == of.id);
    // ASSERT_TRUE(tour.customersid == cu.id);
    // ASSERT_TRUE(tour.employeesid == emp.id);
    // ASSERT_TRUE(tour.reserved_tickets == ticket_count);
    // ASSERT_TRUE(tour.insurance == insurance);
    // ASSERT_TRUE(tour.extra_meals == extra_meals);
    // ASSERT_TRUE(tour.debt == debt);
  }));


}
