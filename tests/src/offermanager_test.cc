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
    offer_t offer;
    offer.id =1;
    offer.name ="wycieczka 1";
    offer.country ="tokio";
    offer.city ="japonia";
    offer.date_begin =str2epoch("14.01.2019");
    offer.date_end =str2epoch("20.01.2019");
    offer.price = 6412;
    offer.insurance_cost =300;
    offer.extra_meals_cost =200;
    offer.categoryid = 1;
    offer.tickets_count = 55;
    offers.push_back(offer);

    offer.id =2;
    offer.name ="wycieczka 2";
    offer.country ="meksyk";
    offer.city ="meksyk-city";
    offer.date_begin =str2epoch("15.01.2019");
    offer.date_end =str2epoch("20.01.2019");
    offer.price = 4298;
    offer.insurance_cost =614;
    offer.extra_meals_cost =538;
    offer.categoryid = 4;
    offer.tickets_count = 55;
    offers.push_back(offer);

    offer.id =3;
    offer.name ="wycieczka 3";
    offer.country ="nowy jork";
    offer.city ="usa";
    offer.date_begin =str2epoch("16.01.2019");
    offer.date_end =str2epoch("22.01.2019");
    offer.price = 6990;
    offer.insurance_cost =795;
    offer.extra_meals_cost =385;
    offer.categoryid = 2;
    offer.tickets_count = 46;
    offers.push_back(offer);

    tour_t  tour;
    tour.id = 1;
    tour.debt =1379;
    tour.insurance = 1;
    tour.extra_meals =0;
    tour.state =static_cast<tour_state>(0);
    tour.reserved_tickets =4;
    tour.customersid = 1;
    tour.employeesid = 1;
    tour.offerid = 1;
    tours.push_back(tour);

    tour.id = 2;
    tour.debt =1062;
    tour.insurance = 1;
    tour.extra_meals =1;
    tour.state =static_cast<tour_state>(0);
    tour.reserved_tickets =5;
    tour.customersid = 2;
    tour.employeesid = 1;
    tour.offerid = 2;
    tours.push_back(tour);

    tour.id = 3;
    tour.debt =2509;
    tour.insurance = 1;
    tour.extra_meals =1;
    tour.state =static_cast<tour_state>(0);
    tour.reserved_tickets =3;
    tour.customersid = 3;
    tour.employeesid = 1;
    tour.offerid = 3;
    tours.push_back(tour);
  }
  std::vector<offer_t> offers;
  std::vector<tour_t> tours;
};

TEST_F(OfferManagerTest, modify_modifies_existing_offer_passed_with_correct_debt_callculation)
{
  ASSERT_TRUE(offers.size() > 0);
  ASSERT_TRUE(tours.size() > 0);

  hldb_mock hldb_mocked_instance("");
  offer_manager offer_manager_instance(hldb_mocked_instance);

  auto modified_offer = offers[0];
  EXPECT_CALL(hldb_mocked_instance, get_offers_like(modified_offer.id))
    .Times(1)
    .WillOnce(Return(modified_offer));

  modified_offer.price = 7000;
  modified_offer.insurance_cost = 400;
  modified_offer.extra_meals_cost = 200;

  std::vector<tour_t> selected_tours;
  std::copy_if(tours.begin(),
               tours.end(),
               std::back_inserter(selected_tours),
               [&modified_offer](tour_t &t){ if (t.offerid == modified_offer.id) return true; else return false; });
  tour_t tour;
  tour.offerid = modified_offer.id;
  EXPECT_CALL(hldb_mocked_instance, get_tours_like(tour))
    .Times(1)
    .WillOnce(Return(selected_tours));

  int expected_callculated_cost = 4131;
  int callculated_cost;
  ON_CALL(hldb_mocked_instance, modify_tour).WillByDefault(Invoke([&](const tour_t &t) ->bool{
    callculated_cost = t.debt;
    return t.valid();
  }));
  offer_t offer_after_modify_function_call;
  ON_CALL(hldb_mocked_instance, modify_offer)
    .WillByDefault(Invoke([&offer_after_modify_function_call](const offer_t &o) -> bool {
      offer_after_modify_function_call = o;
      return o.valid();
    }));

  EXPECT_CALL(hldb_mocked_instance,modify_tour).Times(1);
  EXPECT_CALL(hldb_mocked_instance,modify_offer).Times(1);

  ASSERT_TRUE(offer_manager_instance.modify(modified_offer));
  EXPECT_EQ(callculated_cost, expected_callculated_cost);
  EXPECT_TRUE(offer_after_modify_function_call.id == modified_offer.id);
  EXPECT_TRUE(offer_after_modify_function_call.name == modified_offer.name);
  EXPECT_TRUE(offer_after_modify_function_call.country == modified_offer.country);
  EXPECT_TRUE(offer_after_modify_function_call.city == modified_offer.city);
  EXPECT_TRUE(offer_after_modify_function_call.date_begin == modified_offer.date_begin);
  EXPECT_TRUE(offer_after_modify_function_call.date_end == modified_offer.date_end);
  EXPECT_TRUE(offer_after_modify_function_call.price == modified_offer.price);
  EXPECT_TRUE(offer_after_modify_function_call.insurance_cost == modified_offer.insurance_cost);
  EXPECT_TRUE(offer_after_modify_function_call.extra_meals_cost == modified_offer.extra_meals_cost);
  EXPECT_TRUE(offer_after_modify_function_call.categoryid == modified_offer.categoryid);
  EXPECT_TRUE(offer_after_modify_function_call.tickets_count == modified_offer.tickets_count);
}

TEST_F(OfferManagerTest, modify_modifies_existing_offer_failed)
{
  ASSERT_TRUE(offers.size() > 0);
  ASSERT_TRUE(tours.size() > 0);

  hldb_mock hldb_mocked_instance("");
  offer_manager offer_manager_instance(hldb_mocked_instance);
  auto modified_offer = offers[0];
  app::sql::set_invalid(modified_offer.id);

  EXPECT_CALL(hldb_mocked_instance, get_offers_like(modified_offer.id))
    .Times(1)
    .WillOnce(Return(modified_offer));

  modified_offer.price = 7000;
  modified_offer.insurance_cost = 400;
  modified_offer.extra_meals_cost = 300;
  ASSERT_FALSE(offer_manager_instance.modify(modified_offer));
}

TEST_F(OfferManagerTest, drop_disabling_existing_offer_passed_with_clients_payment_return)
{
  ASSERT_TRUE(offers.size() > 0);
  ASSERT_TRUE(tours.size() > 0);

  hldb_mock hldb_mocked_instance("");
  offer_manager offer_manager_instance(hldb_mocked_instance);

  auto dropped_offer = offers[0];
  EXPECT_CALL(hldb_mocked_instance, get_offers_like(dropped_offer.id))
    .Times(1)
    .WillOnce(Return(dropped_offer));

  std::vector<tour_t> selected_tours;
  std::copy_if(tours.begin(),
               tours.end(),
               std::back_inserter(selected_tours),
               [&dropped_offer](tour_t &t){ if (t.offerid == dropped_offer.id) return true; else return false; });

  tour_t modified_tour = tours[0];
  EXPECT_CALL(hldb_mocked_instance, get_tours_like(modified_tour))
    .Times(1)
    .WillOnce(Return(selected_tours));

  constexpr int expected_callculated_cost =25469;
  int callculated_cost;
  ON_CALL(hldb_mocked_instance, modify_tour).WillByDefault(Invoke([&](const tour_t &t) ->bool{
    callculated_cost = t.debt;
    return t.valid();
  }));
  offer_t offer_after_modify_function_call;
  ON_CALL(hldb_mocked_instance, modify_offer)
    .WillByDefault(Invoke([&offer_after_modify_function_call](const offer_t &o) -> bool {
      offer_after_modify_function_call = o;
      return o.valid();
    }));

  EXPECT_CALL(hldb_mocked_instance,modify_tour).Times(1);
  EXPECT_CALL(hldb_mocked_instance,modify_offer).Times(1);

  ASSERT_TRUE(offer_manager_instance.drop_offer(dropped_offer.id));
  EXPECT_EQ(callculated_cost, expected_callculated_cost);
  EXPECT_TRUE(offer_after_modify_function_call.id == dropped_offer.id);
  EXPECT_TRUE(offer_after_modify_function_call.name == dropped_offer.name);
  EXPECT_TRUE(offer_after_modify_function_call.country == dropped_offer.country);
  EXPECT_TRUE(offer_after_modify_function_call.city == dropped_offer.city);
  EXPECT_TRUE(offer_after_modify_function_call.date_begin == date_t(tb(-1)));
  EXPECT_TRUE(offer_after_modify_function_call.date_end == date_t(tb(-1)));
  EXPECT_TRUE(offer_after_modify_function_call.price == dropped_offer.price);
  EXPECT_TRUE(offer_after_modify_function_call.insurance_cost == dropped_offer.insurance_cost);
  EXPECT_TRUE(offer_after_modify_function_call.extra_meals_cost == dropped_offer.extra_meals_cost);
  EXPECT_TRUE(offer_after_modify_function_call.categoryid == dropped_offer.categoryid);
  EXPECT_TRUE(offer_after_modify_function_call.tickets_count == dropped_offer.tickets_count);
}


TEST_F(OfferManagerTest, drop_disabling_existing_offer_failled)
{
  ASSERT_TRUE(offers.size() > 0);
  ASSERT_TRUE(tours.size() > 0);

  hldb_mock hldb_mocked_instance("");
  offer_manager offer_manager_instance(hldb_mocked_instance);
  auto modified_offer = offers[0];
  app::sql::set_invalid(modified_offer.id);

  EXPECT_CALL(hldb_mocked_instance, get_offers_like(modified_offer.id))
    .Times(1)
    .WillOnce(Return(modified_offer));

  ASSERT_FALSE(offer_manager_instance.drop_offer(modified_offer.id));
}