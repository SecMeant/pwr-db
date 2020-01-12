#include "credentials_manipulator.h"
#include "../../reflect.h"
#include "../data_access_manager.h"
#include "hldb.h"
#include <fmt/format.h>
#include <sstream>
namespace app::dbaccess {
  std::vector<credentials_t>
  credentials_manipulator::get_all() const noexcept
  {

    auto *hldb_inst = this->parent()->parent();
    auto res = hldb_inst->raw_query_res(
      "SELECT id, employeeid, login, pass_hash, privilege "
      "FROM credentials");
    credentials_t credentials;
    std::vector<credentials_t> data{};
    if (res == nullptr)
      return data;

    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      credentials.id = atoi(row[0]);
      credentials.employeeid = atoi(row[1]);
      credentials.login = row[2];
      credentials.pass_hash = row[3];
      credentials.privilege =
        static_cast<logic::privilege_level>(atoi(row[4]));
      data.push_back(credentials);
    }
    return data;
  }

  std::vector<credentials_t>
  credentials_manipulator::get_like(const credentials_t &entity) const
    noexcept
  {
    std::stringstream command;
    command << "SELECT id, employeeid, login, pass_hash, privilege "
               "FROM credentials WHERE";

    auto params = glue_params(entity, " and ");

    credentials_t credentials;
    std::vector<credentials_t> data{};

    if (params == "")
      return data;

    command << params;
    auto *hldb_inst = this->parent()->parent();
    auto res = hldb_inst->raw_query_res(command.str());
    if (res == nullptr)
      return data;

    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      credentials.id = atoi(row[0]);
      credentials.employeeid = atoi(row[1]);
      credentials.login = row[2];
      credentials.pass_hash = row[3];
      credentials.privilege =
        static_cast<logic::privilege_level>(atoi(row[4]));
      data.push_back(credentials);
    }

    return data;
  }

  credentials_t
  credentials_manipulator::get(int id) const noexcept
  {
    auto *hldb_inst = this->parent()->parent();
    auto command =
      fmt::format("SELECT * from credentials WHERE id = {}", id);
    auto res = hldb_inst->raw_query_res(command);
    credentials_t credentials = {};

    if (!res || mysql_num_rows(res.get()) != 1)
      return credentials;

    auto row = mysql_fetch_row(res.get());

    credentials.id = atoi(row[0]);
    credentials.employeeid = atoi(row[1]);
    credentials.login = row[2];
    credentials.pass_hash = row[3];
    credentials.privilege =
      static_cast<logic::privilege_level>(atoi(row[4]));

    return credentials;
  }

  bool
  credentials_manipulator::add(const credentials_t &entity) const noexcept
  {
    std::string command = "INSERT INTO credentials "
                          "(id,employeeid,login,pass_hash) "
                          "VALUES (\'{}\', \'{}\', \'{}\', {});";

    command = fmt::format(command,
                          entity.id,
                          entity.employeeid,
                          entity.login,
                          entity.pass_hash,
                          entity.privilege);

    auto *hldb_inst = this->parent()->parent();
    return !hldb_inst->raw_query(command);
  }

  bool
  credentials_manipulator::modify(const credentials_t &entity) const
    noexcept
  {
    std::stringstream command;
    command << "UPDATE credentials SET";

    auto params = glue_params(entity, ", ");

    if (params == "")
      return false;
    command << params;
    command << fmt::format("WHERE id = {}", entity.id);

    auto *hldb_inst = this->parent()->parent();
    return !hldb_inst->raw_query(command.str());
  }

  bool
  credentials_manipulator::remove(int id) const noexcept
  {
    std::string command =
      fmt::format("DELETE from credentials WHERE id = {}", id);
    auto *hldb_inst = this->parent()->parent();
    return !hldb_inst->raw_query(command);
  }

  data_access_manager *
  credentials_manipulator::parent() const noexcept
  {
    return container_of(
      this, data_access_manager, m_credentials_manipulator);
  }

  std::string
  credentials_manipulator::glue_params(const credentials_t &entity,
                                       std::string separator) const
    noexcept
  {
    std::stringstream params;
    bool concat = false;
    if (!sql::any(entity.id)) {
      params << fmt::format(" id = \'{}\' ", entity.id);
      concat = true;
    }

    if (!sql::any(entity.employeeid)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" employeeid = \'{}\' ", entity.employeeid);
    }

    if (!sql::any(entity.login)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" login = \'{}\' ", entity.login);
    }

    if (!sql::any(entity.pass_hash)) {
      if (concat)
        params << fmt::format(" {} ", separator);

      params << fmt::format(" pass_hash = {} ", entity.pass_hash);
    }

    if (!sql::any(entity.privilege)) {
      if (concat)
        params << fmt::format(" {} ", separator);

      params << fmt::format(" privilege = {} ",
                            static_cast<int>(entity.privilege));
    }

    return params.str();
  }

} // namespace app::dbaccess
