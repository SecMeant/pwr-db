#include "category_manipulator.h"
#include "../../reflect.h"
#include "../data_access_manager.h"
#include "hldb.h"
#include <fmt/format.h>
#include <sstream>

namespace app::dbaccess {
  std::vector<category_t>
  category_manipulator::get_all() const noexcept
  {

    auto *hldb_inst = this->parent()->parent();
    auto res = hldb_inst->raw_query_res(
      "SELECT id, name, login, pass_hash, privilege "
      "FROM category");
    category_t category;
    std::vector<category_t> data{};
    if (res == nullptr)
      return data;

    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      category.id = atoi(row[0]);
      category.name = atoi(row[1]);
      data.push_back(category);
    }
    return data;
  }

  std::vector<category_t>
  category_manipulator::get_like(const category_t &entity) const noexcept
  {
    std::stringstream command;
    command << "SELECT id, name, login, pass_hash, privilege "
               "FROM category WHERE";

    auto params = glue_params(entity, " and ");

    category_t category;
    std::vector<category_t> data{};

    if (params == "")
      return data;

    command << params;
    auto *hldb_inst = this->parent()->parent();
    auto res = hldb_inst->raw_query_res(command.str());
    if (res == nullptr)
      return data;

    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      category.id = atoi(row[0]);
      category.name = atoi(row[1]);
      data.push_back(category);
    }

    return data;
  }

  category_t
  category_manipulator::get(int id) const noexcept
  {
    auto *hldb_inst = this->parent()->parent();
    auto command = fmt::format("SELECT * from category WHERE id = {}", id);
    auto res = hldb_inst->raw_query_res(command);
    category_t category = {};

    if (!res || mysql_num_rows(res.get()) != 1)
      return category;

    auto row = mysql_fetch_row(res.get());

    category.id = atoi(row[0]);
    category.name = atoi(row[1]);
    return category;
  }

  bool
  category_manipulator::add(const category_t &entity) const noexcept
  {
    std::string command = "INSERT INTO category "
                          "(id,name,login,pass_hash) "
                          "VALUES (\'{}\', \'{}\', \'{}\', {});";

    command = fmt::format(command, entity.id, entity.name);
    auto *hldb_inst = this->parent()->parent();
    return !hldb_inst->raw_query(command);
  }

  bool
  category_manipulator::modify(const category_t &entity) const noexcept
  {
    std::stringstream command;
    command << "UPDATE category SET";

    auto params = glue_params(entity, ", ", "=");

    if (params == "")
      return false;
    command << params;
    command << fmt::format("WHERE id = {}", entity.id);

    auto *hldb_inst = this->parent()->parent();
    return !hldb_inst->raw_query(command.str());
  }

  bool
  category_manipulator::remove(int id) const noexcept
  {
    std::string command =
      fmt::format("DELETE from category WHERE id = {}", id);
    auto *hldb_inst = this->parent()->parent();
    return !hldb_inst->raw_query(command);
  }

  data_access_manager *
  category_manipulator::parent() const noexcept
  {
    return container_of(this, data_access_manager, m_category_manipulator);
  }

  std::string
  category_manipulator::glue_params(const category_t &entity,
                                    std::string_view separator,
                                    std::string_view eq) const noexcept
  {
    std::stringstream params;
    bool concat = false;
    if (!sql::any(entity.id)) {
      params << fmt::format(" id = \'{}\' ", entity.id);
      concat = true;
    }

    if (!sql::any(entity.name)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" name {} \'{}\' ", eq, entity.name);
    }
    return params.str();
  }

} // namespace app::dbaccess
