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


  hldb_mock hm("ghjk");
  offer_manager om(hm);

  auto old_off = offers[0];
  EXPECT_CALL(hm, get_offers_like(old_off.id))
    .Times(1)
    .WillOnce(Return(old_off));

  offer_t new_off = old_off;
  int price = 7000;
  int insurance_cost = 400;
  int extra_meals_cost = 200;
  new_off.price = price;
  new_off.insurance_cost = insurance_cost;
  new_off.extra_meals_cost = extra_meals_cost;

  std::vector<tour_t> selected_tours;
  std::copy_if(tours.begin(), tours.end(),std::back_inserter(selected_tours),[&new_off](tour_t &t){ if (t.offerid == new_off.id) return true; else return false; });

  tour_t t_ref = tours[0];
  EXPECT_CALL(hm, get_tours_like(t_ref))
    .Times(1)
    .WillOnce(Return(selected_tours));

  bool  cost_invalid;
  constexpr int clacluated_cost_diff = 4131;
  ON_CALL(hm, modify_tour).WillByDefault(Invoke([&](const tour_t &t) ->bool{
    cost_invalid = (t.debt == clacluated_cost_diff);
    return t.valid();
  }));


  offer_t off_from_call;
  ON_CALL(hm, modify_offer)
    .WillByDefault(Invoke([&off_from_call](const offer_t &o) -> bool {
      off_from_call = o;
      return o.valid();
    }));
  EXPECT_CALL(hm,modify_tour).Times(1);
  EXPECT_CALL(hm,modify_offer).Times(1);

  ASSERT_TRUE(om.modify(new_off));

  ASSERT_TRUE(cost_invalid);
  ASSERT_TRUE(off_from_call.id == new_off.id);
  ASSERT_TRUE(off_from_call.name == new_off.name);
  ASSERT_TRUE(off_from_call.country == new_off.country);
  ASSERT_TRUE(off_from_call.city == new_off.city);
  ASSERT_TRUE(off_from_call.date_begin == new_off.date_begin);
  ASSERT_TRUE(off_from_call.date_end == new_off.date_end);
  ASSERT_TRUE(off_from_call.price == new_off.price);
  ASSERT_TRUE(off_from_call.insurance_cost == new_off.insurance_cost);
  ASSERT_TRUE(off_from_call.extra_meals_cost == new_off.extra_meals_cost);
  ASSERT_TRUE(off_from_call.categoryid == new_off.categoryid);
  ASSERT_TRUE(off_from_call.tickets_count == new_off.tickets_count);
}
