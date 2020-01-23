#pragma once

#include <gmock/gmock.h>
#include "hldb.h"

namespace app::logic {
  class hldb_mock : public hldb_i
  {
    public:
    hldb_mock(std::string dbname) {};
    MOCK_METHOD(std::vector<dbaccess::customer_t>, get_all_customers, ());
    MOCK_METHOD(std::vector<dbaccess::credentials_t>, get_all_credentials, ());
    MOCK_METHOD(std::vector<dbaccess::offer_t>, get_all_offers, ());
    MOCK_METHOD(std::vector<dbaccess::employee_t>, get_all_employees, ());
    MOCK_METHOD(std::vector<dbaccess::tour_t>, get_all_tours, ());
    MOCK_METHOD(std::vector<dbaccess::category_t>, get_all_category, ());

    MOCK_METHOD(std::vector<dbaccess::customer_t>, get_customers_like, (const dbaccess::customer_t &));
    MOCK_METHOD(std::vector<dbaccess::credentials_t>, get_credentials_like, (const dbaccess::credentials_t &));
    MOCK_METHOD(std::vector<dbaccess::offer_t>, get_offers_like, (const dbaccess::offer_t &));
    MOCK_METHOD(std::vector<dbaccess::employee_t>, get_employees_like, (const dbaccess::employee_t &));
    MOCK_METHOD(std::vector<dbaccess::tour_t>, get_tours_like, (const dbaccess::tour_t &));
    MOCK_METHOD(std::vector<dbaccess::category_t>, get_category_like, (const dbaccess::category_t &));

    MOCK_METHOD(dbaccess::customer_t, get_customers_like, (int id));
    MOCK_METHOD(dbaccess::credentials_t, get_credentials_like, (int id));
    MOCK_METHOD(dbaccess::offer_t, get_offers_like, (int id));
    MOCK_METHOD(dbaccess::employee_t, get_employees_like, (int id));
    MOCK_METHOD(dbaccess::tour_t, get_tours_like, (int id));
    MOCK_METHOD(dbaccess::category_t, get_category_like, (int id));

    MOCK_METHOD(bool, add_customer, (const dbaccess::customer_t &));
    MOCK_METHOD(bool, add_offer, (const dbaccess::offer_t &));
    MOCK_METHOD(bool, add_employee, (const dbaccess::employee_t &));
    MOCK_METHOD(bool, add_tour, (const dbaccess::tour_t &));
    MOCK_METHOD(bool, add_category, (const dbaccess::category_t &));

    MOCK_METHOD(bool, remove_customer, (int id));
    MOCK_METHOD(bool, remove_offer, (int id));
    MOCK_METHOD(bool, remove_employee, (int id));
    MOCK_METHOD(bool, remove_tour, (int id));
    MOCK_METHOD(bool, remove_category, (int id));

    MOCK_METHOD(bool, modify_customer, (const dbaccess::customer_t &));
    MOCK_METHOD(bool, modify_offer, (const dbaccess::offer_t &));
    MOCK_METHOD(bool, modify_employee, (const dbaccess::employee_t &));
    MOCK_METHOD(bool, modify_tour, (const dbaccess::tour_t &));
    MOCK_METHOD(bool, modify_category, (const dbaccess::category_t &));

    MOCK_METHOD(bool, login, (std::string_view, std::string_view));
    MOCK_METHOD(bool, authenticate, (std::string_view, std::string_view));
    MOCK_METHOD(bool, make_reservation, (int off_id, int cus_id, int ticket_count, bool insurance, bool extra_meals));
    MOCK_METHOD(bool, drop_reservation, (int id));
    MOCK_METHOD(bool, modify_reservation, (const dbaccess::tour_t &t1));
    MOCK_METHOD(bool, raw_query, (const std::string &t1));
    MOCK_METHOD(dbaccess::mysql_res_t, raw_query_res, (const std::string &t1));
    MOCK_METHOD(const dbaccess::employee_t &, get_logged_user, ());
    MOCK_METHOD(std::string, hash, (std::string_view s));
    MOCK_METHOD(dbaccess::category_t, get_category_by_id, (int id));
    MOCK_METHOD(int, get_category_id_by_name, (std::string_view catname));
    MOCK_METHOD(logic::privilege_level, get_user_privilage, ());
  };
} // namespace app::logic
