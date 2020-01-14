#include "offer_manipulator.h"
#include "../../reflect.h"
#include "../data_access_manager.h"
#include "hldb.h"
#include <fmt/format.h>
#include <sstream>
namespace app::dbaccess {
  std::vector<offer_t>
  offer_manipulator::get_all() const noexcept
  {

    auto *hldb_impl = this->parent()->parent();
    auto res = hldb_impl->raw_query_res(
      "SELECT "
      "id,name,country,city,tickets_count,DATE_FORMAT(date_begin,'%d.%m.%"
      "Y'),DATE_FORMAT(date_end,'%d.%m.%Y'),price,categoryid,insurance_"
      "cost,extra_meals_cost from offers");

    offer_t offer;
    std::vector<offer_t> data{};
    if (res == nullptr)
      return data;
    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      offer.id = atoi(row[0]);
      offer.name = row[1];
      offer.country = row[2];
      offer.city = row[3];
      offer.tickets_count = atoi(row[4]);
      offer.date_begin = str2epoch(row[5]);
      offer.date_end = str2epoch(row[6]);
      offer.price = atoi(row[7]);
      offer.categoryid = atoi(row[8]);
      offer.insurance_cost = atoi(row[9]);
      offer.extra_meals_cost = atoi(row[10]);
      data.push_back(offer);
    }
    return data;
  }

  std::vector<offer_t>
  offer_manipulator::get_like(const offer_t &entity) const noexcept
  {
    std::stringstream command;
    command
      << "SELECT "
         "id,name,country,city,tickets_count,DATE_FORMAT(date_begin,'%d.%"
         "m.%Y'),DATE_FORMAT(date_end,'%d.%m.%Y'),price,categoryid,"
         "insurance_cost,extra_meals_cost from offers WHERE";

    auto params = glue_params(entity, " and ");

    offer_t offer;
    std::vector<offer_t> data{};

    if (params == "")
      return data;
    command << params;

    auto *hldb_impl = this->parent()->parent();
    auto res = hldb_impl->raw_query_res(command.str());
    if (res == nullptr)
      return data;

    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      offer.id = atoi(row[0]);
      offer.name = row[1];
      offer.country = row[2];
      offer.city = row[3];
      offer.tickets_count = atoi(row[4]);
      offer.date_begin = str2epoch(row[5]);
      offer.date_end = str2epoch(row[6]);
      offer.price = atoi(row[7]);
      offer.categoryid = atoi(row[8]);
      offer.insurance_cost = atoi(row[9]);
      offer.extra_meals_cost = atoi(row[10]);
      data.push_back(offer);
    }
    return data;
  }

  offer_t
  offer_manipulator::get(int id) const noexcept
  {
    auto *hldb_impl = this->parent()->parent();
    auto command = fmt::format(
      "SELECT "
      "id,name,country,city,tickets_count,DATE_FORMAT(date_begin,'%d.%m.%"
      "Y'),DATE_FORMAT(date_end,'%d.%m.%Y'),price,categoryid,insurance_"
      "cost,extra_meals_cost from offers WHERE id = {}",
      id);
    auto res = hldb_impl->raw_query_res(command);
    offer_t offer;
    if (!res || mysql_num_rows(res.get()) != 1)
      return offer;

    auto row = mysql_fetch_row(res.get());
    offer.id = atoi(row[0]);
    offer.name = row[1];
    offer.country = row[2];
    offer.city = row[3];
    offer.tickets_count = atoi(row[4]);
    offer.date_begin = str2epoch(row[5]);
    offer.date_end = str2epoch(row[6]);
    offer.price = atoi(row[7]);
    offer.categoryid = atoi(row[8]);
    offer.insurance_cost = atoi(row[9]);
    offer.extra_meals_cost = atoi(row[10]);
    return offer;
  }

  bool
  offer_manipulator::add(const offer_t &entity) const noexcept
  {
    std::string command =
      "INSERT INTO offers (name,country,city, date_begin, date_end, "
      "price, insurance_cost, extra_meals_cost, categoryid, "
      "tickets_count) VALUES (\'{}\', \'{}\', \'{}\', "
      "STR_TO_DATE(\'{}\',\'%d.%m.%y\'), "
      "STR_TO_DATE(\'{}\',\'%d.%m.%y\'), {}, {}, {}, {}, {})";
    command = fmt::format(command,
                          entity.name,
                          entity.country,
                          entity.city,
                          str2base_str(epoch2str(entity.date_begin)),
                          str2base_str(epoch2str(entity.date_end)),
                          entity.price,
                          entity.insurance_cost,
                          entity.extra_meals_cost,
                          entity.categoryid,
                          entity.tickets_count);

    auto *hldb_impl = this->parent()->parent();
    return !hldb_impl->raw_query(command);
  }

  bool
  offer_manipulator::modify(const offer_t &entity) const noexcept
  {
    std::stringstream command;
    command << "UPDATE offers SET";

    auto params = glue_params(entity, ", ");

    if (params == "")
      return false;
    command << params;
    command << fmt::format("WHERE id = {}", entity.id);

    auto *hldb_impl = this->parent()->parent();
    return !hldb_impl->raw_query(command.str());
  }

  bool
  offer_manipulator::remove(int id) const noexcept
  {
    std::string command =
      fmt::format("DELETE from offers WHERE id = {}", id);
    auto *hldb_impl = this->parent()->parent();
    return !hldb_impl->raw_query(command);
  }

  data_access_manager *
  offer_manipulator::parent() const noexcept
  {
    return container_of(this, data_access_manager, m_offer_manipulator);
  }

  std::string
  offer_manipulator::glue_params(const offer_t &entity,
                                 std::string separator) const noexcept
  {
    std::stringstream params;
    bool concat = false;
    if (!sql::any(entity.name)) {
      params << fmt::format(" name = \'{}\' ", entity.name);
      concat = true;
    }

    if (!sql::any(entity.country)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" country = \'{}\' ", entity.country);
    }

    if (!sql::any(entity.date_begin)) {
      auto date = str2base_str(epoch2str(entity.date_begin));
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(
        " date_begin = STR_TO_DATE(\'{}\',\'%d.%m.%y\') ", date);
    }

    if (!sql::any(entity.date_end)) {
      auto date = str2base_str(epoch2str(entity.date_end));
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(
        " date_end = STR_TO_DATE(\'{}\',\'%d.%m.%y\') ", date);
    }

    if (!sql::any(entity.price)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" price = {} ", entity.price);
    }

    if (!sql::any(entity.insurance_cost)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" insurance_cost = {} ",
                            entity.insurance_cost);
    }

    if (!sql::any(entity.extra_meals_cost)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" extra_meals_cost = {} ",
                            entity.extra_meals_cost);
    }

    if (!sql::any(entity.categoryid)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" categoryid = {} ", entity.categoryid);
    }

    if (!sql::any(entity.tickets_count)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" tickets_count = {} ", entity.tickets_count);
    }
    return params.str();
  }

} // namespace app::dbaccess
