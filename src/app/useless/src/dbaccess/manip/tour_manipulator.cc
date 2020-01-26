#include "tour_manipulator.h"
#include "../../reflect.h"
#include "../data_access_manager.h"
#include "hldb.h"
#include <fmt/format.h>
#include <sstream>
namespace app::dbaccess {
  std::vector<tour_t>
  tour_manipulator::get_all() const noexcept
  {

    auto *hldb_impl = this->parent()->parent();
    auto res = hldb_impl->raw_query_res("SELECT * from tour");

    tour_t tour;
    std::vector<tour_t> data{};
    if (res == nullptr)
      return data;
    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      tour.id = atoi(row[0]);
      tour.debt = atoi(row[1]);
      tour.insurance = atoi(row[2]);
      tour.extra_meals = atoi(row[3]);
      tour.state = static_cast<tour_state>(atoi(row[4]));
      tour.reserved_tickets = atoi(row[5]);
      tour.customersid = atoi(row[6]);
      tour.employeesid = atoi(row[7]);
      tour.offerid = atoi(row[8]);
      data.push_back(tour);
    }
    return data;
  }

  std::vector<tour_t>
  tour_manipulator::get_like(const tour_t &entity) const noexcept
  {
    std::stringstream command;
    command << "SELECT * from tour WHERE";

    auto params = glue_params(entity, " and ");

    tour_t tour;
    std::vector<tour_t> data{};

    if (params == "")
      return data;
    command << params;

    auto *hldb_impl = this->parent()->parent();
    auto res = hldb_impl->raw_query_res(command.str());
    if (res == nullptr)
      return data;

    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      tour.id = atoi(row[0]);
      tour.debt = atoi(row[1]);
      tour.insurance = atoi(row[2]);
      tour.extra_meals = atoi(row[3]);
      tour.state = static_cast<tour_state>(atoi(row[4]));
      tour.reserved_tickets = atoi(row[5]);
      tour.customersid = atoi(row[6]);
      tour.employeesid = atoi(row[7]);
      tour.offerid = atoi(row[8]);
      data.push_back(tour);
    }

    return data;
  }

  tour_t
  tour_manipulator::get(int id) const noexcept
  {
    auto command = fmt::format("SELECT * from tour WHERE id = {}", id);
    auto *hldb_impl = this->parent()->parent();
    auto res = hldb_impl->raw_query_res(command);
    tour_t tour;
    if (!res || mysql_num_rows(res.get()) != 1)
      return tour;

    auto row = mysql_fetch_row(res.get());
    tour.id = atoi(row[0]);
    tour.debt = atoi(row[1]);
    tour.insurance = atoi(row[2]);
    tour.extra_meals = atoi(row[3]);
    tour.state = static_cast<tour_state>(atoi(row[4]));
    tour.reserved_tickets = atoi(row[5]);
    tour.customersid = atoi(row[6]);
    tour.employeesid = atoi(row[7]);
    tour.offerid = atoi(row[8]);
    return tour;
  }

  bool
  tour_manipulator::add(const tour_t &entity) const noexcept
  {
    std::string command =
      "INSERT INTO tour (CustomerId, employeeid, offerid, insurance, "
      "extra_meals, debt, state, reserved_tickets)  VALUES ({}, {}, {}, "
      "{}, {}, {}, {}, {})";
    command = fmt::format(command,
                          entity.customersid,
                          entity.employeesid,
                          entity.offerid,
                          entity.insurance,
                          entity.extra_meals,
                          entity.debt,
                          entity.state,
                          entity.reserved_tickets);
    auto *hldb_impl = this->parent()->parent();
    return hldb_impl->raw_query(command);
  }

  bool
  tour_manipulator::modify(const tour_t &entity) const noexcept
  {
    std::stringstream command;
    command << "UPDATE tour SET";

    auto params = glue_params(entity, ", ", "=");

    if (params == "")
      return false;
    command << params;
    command << fmt::format("WHERE id = {}", entity.id);

    auto *hldb_impl = this->parent()->parent();
    return hldb_impl->raw_query(command.str());
  }

  bool
  tour_manipulator::remove(int id) const noexcept
  {
    std::string command =
      fmt::format("DELETE from tour WHERE id = {}", id);
    auto *hldb_impl = this->parent()->parent();
    return hldb_impl->raw_query(command);
  }

  data_access_manager *
  tour_manipulator::parent() const noexcept
  {
    return container_of(this, data_access_manager, m_tour_manipulator);
  }

  std::string
  tour_manipulator::glue_params(const tour_t &entity,
                                std::string_view separator,
                                std::string_view eq) const noexcept
  {
    std::stringstream params;
    bool concat = false;
    if (!sql::any(entity.debt)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" debt {} {} ", eq, entity.debt);
    }

    if (!sql::any(entity.insurance)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" insurance {} {} ", eq, entity.insurance);
    }
    if (!sql::any(entity.extra_meals)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" extra_meals {} {} ", eq, entity.extra_meals);
    }

    if (!sql::any(entity.state)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" state {} {} ", eq, entity.state);
    }

    if (!sql::any(entity.customersid)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" customerid {} {} ", eq, entity.customersid);
    }

    if (!sql::any(entity.employeesid)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" employeeid {} {} ", eq, entity.employeesid);
    }

    if (!sql::any(entity.offerid)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" offerid {} {} ", eq, entity.offerid);
    }

    if (!sql::any(entity.reserved_tickets)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" reserved_tickets {} {} ",
                            eq,
                            entity.reserved_tickets);
    }

    return params.str();
  }

} // namespace app::dbaccess
