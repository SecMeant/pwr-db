#include "customer_manipulator.h"
#include "../../reflect.h"
#include "../data_access_manager.h"
#include "hldb.h"
#include <fmt/format.h>
#include <sstream>
namespace app::dbaccess {
  std::vector<customer_t>
  customer_manipulator::get_all() const noexcept
  {

    auto *hldb_impl = this->parent()->parent();
    auto res = hldb_impl->raw_query_res("SELECT * from customers");
    customer_t customer;
    std::vector<customer_t> data{};
    if (res == nullptr)
      return data;

    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      customer.id = atoi(row[0]);
      customer.pesel = fmt::format("{:0<12}", row[1]);
      customer.name = row[2];
      customer.surname = row[3];
      customer.email = row[4];
      data.push_back(customer);
    }
    return data;
  }

  std::vector<customer_t>
  customer_manipulator::get_like(const customer_t &entity) const noexcept
  {
    std::stringstream command;
    command << "SELECT * from customers WHERE";

    auto params = glue_params(entity, " and ");

    customer_t customer;
    std::vector<customer_t> data{};

    if (params == "")
      return data;

    command << params;
    auto *hldb_impl = this->parent()->parent();
    auto res = hldb_impl->raw_query_res(command.str());
    if (res == nullptr)
      return data;

    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      customer.id = atoi(row[0]);
      customer.pesel = fmt::format("{:0<12}", row[1]);
      customer.name = row[2];
      customer.surname = row[3];
      customer.email = row[4];
      data.push_back(customer);
    }

    return data;
  }

  customer_t
  customer_manipulator::get(int id) const noexcept
  {
    auto *hldb_impl = this->parent()->parent();
    auto command =
      fmt::format("SELECT * from customers WHERE id = {}", id);
    auto res = hldb_impl->raw_query_res(command);
    customer_t customer = {};
    if (!res || mysql_num_rows(res.get()) != 1)
      return customer;
    auto row = mysql_fetch_row(res.get());
    customer.id = id;
    customer.pesel = fmt::format("{:0<12}", row[1]);
    customer.name = row[2];
    customer.surname = row[3];
    customer.email = row[4];
    return customer;
  }

  bool
  customer_manipulator::add(const customer_t &entity) const noexcept
  {
    std::string command =
      "INSERT INTO customers  (name,surname,email,pesel) VALUES (\'{}\', "
      "\'{}\', \'{}\', {});";
    command = fmt::format(
      command, entity.name, entity.surname, entity.email, entity.pesel);
    auto *hldb_impl = this->parent()->parent();
    return hldb_impl->raw_query(command);
  }

  bool
  customer_manipulator::modify(const customer_t &entity) const noexcept
  {
    std::stringstream command;
    command << "UPDATE customers SET";

    auto params = glue_params(entity, ", ", "=");

    if (params == "")
      return false;
    command << params;
    command << fmt::format("WHERE id = {}", entity.id);

    auto *hldb_impl = this->parent()->parent();
    return hldb_impl->raw_query(command.str());
  }

  bool
  customer_manipulator::remove(int id) const noexcept
  {
    std::string command =
      fmt::format("DELETE from customers WHERE id = {}", id);
    auto *hldb_impl = this->parent()->parent();
    return hldb_impl->raw_query(command);
  }

  data_access_manager *
  customer_manipulator::parent() const noexcept
  {
    return container_of(this, data_access_manager, m_customer_manipulator);
  }

  std::string
  customer_manipulator::glue_params(const customer_t &entity,
                                    std::string_view separator,
                                    std::string_view eq) const noexcept
  {
    std::stringstream params;
    bool concat = false;
    if (!sql::any(entity.name)) {
      params << fmt::format(" name {} \'{}\' ", eq, entity.name);
      concat = true;
    }

    if (!sql::any(entity.surname)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" surname {} \'{}\' ", eq, entity.surname);
    }

    if (!sql::any(entity.email)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" email {} \'{}\' ", eq, entity.email);
    }

    if (!sql::any(entity.pesel)) {
      if (concat)
        params << fmt::format(" {} ", separator);

      params << fmt::format(" pesel {} {} ", eq, entity.pesel);
    }
    return params.str();
  }

} // namespace app::dbaccess
