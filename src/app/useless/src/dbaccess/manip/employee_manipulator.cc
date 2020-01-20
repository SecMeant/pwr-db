#include "employee_manipulator.h"
#include "../../reflect.h"
#include "../data_access_manager.h"
#include "hldb.h"
#include <fmt/format.h>
#include <sstream>
namespace app::dbaccess {
  std::vector<employee_t>
  employee_manipulator::get_all() const noexcept
  {

    auto *hldb_impl = this->parent()->parent();
    auto res = hldb_impl->raw_query_res(
      "SELECT "
      "id,name,surname,DATE_FORMAT(hire_date,'%d.%m.%Y'),salary,email,"
      "phone_number from employees");

    employee_t employee;
    std::vector<employee_t> data{};
    if (res == nullptr)
      return data;
    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      employee.id = atoi(row[0]);
      employee.name = row[1];
      employee.surname = row[2];
      employee.hire_date = str2epoch(row[3]);
      employee.salary = atoi(row[4]);
      employee.email = row[5];
      employee.phone_number = row[6];
      data.push_back(employee);
    }
    return data;
  }

  std::vector<employee_t>
  employee_manipulator::get_like(const employee_t &entity) const noexcept
  {
    std::stringstream command;
    command << "SELECT "
               "id,name,surname,DATE_FORMAT(hire_date,'%d.%m.%Y'),salary,"
               "email,phone_number from employees WHERE";

    auto params = glue_params(entity, " and ");

    employee_t employee;
    std::vector<employee_t> data{};

    if (params == "")
      return data;
    command << params;

    auto *hldb_impl = this->parent()->parent();
    auto res = hldb_impl->raw_query_res(command.str());
    if (res == nullptr)
      return data;

    for (uint i = 0; i < res->row_count; i++) {
      auto row = mysql_fetch_row(res.get());
      employee.id = atoi(row[0]);
      employee.name = row[1];
      employee.surname = row[2];
      employee.hire_date = str2epoch(row[3]);
      employee.salary = atoi(row[4]);
      employee.email = row[5];
      employee.phone_number = row[6];
      data.push_back(employee);
    }

    return data;
  }

  employee_t
  employee_manipulator::get(int id) const noexcept
  {
    auto *hldb_impl = this->parent()->parent();
    auto command =
      fmt::format("SELECT "
                  "id,name,surname,DATE_FORMAT(hire_date,'%d.%m.%Y'),"
                  "salary,email,phone_number from employees WHERE id = {}",
                  id);
    auto res = hldb_impl->raw_query_res(command);
    employee_t employee;
    if (!res || mysql_num_rows(res.get()) != 1)
      return employee;
    auto row = mysql_fetch_row(res.get());
    employee.id = atoi(row[0]);
    employee.name = row[1];
    employee.surname = row[2];
    employee.hire_date = str2epoch(row[3]);
    employee.salary = atoi(row[4]);
    employee.email = row[5];
    employee.phone_number = row[6];

    return employee;
  }

  bool
  employee_manipulator::add(const employee_t &entity) const noexcept
  {
    std::string command =
      "INSERT INTO employees (name,surname,hire_date, salary, email, "
      "phone_number) VALUES (\'{}\', \'{}\', "
      "STR_TO_DATE(\'{}\',\'%d.%m.%y\'), {}, \'{}\', \'{}\')";
    command = fmt::format(command,
                          entity.name,
                          entity.surname,
                          str2base_str(epoch2str(entity.hire_date)),
                          entity.salary,
                          entity.email,
                          entity.phone_number);
    auto *hldb_impl = this->parent()->parent();
    return !hldb_impl->raw_query(command);
  }

  bool
  employee_manipulator::modify(const employee_t &entity) const noexcept
  {
    std::stringstream command;
    command << "UPDATE employees SET";

    auto params = glue_params(entity, ", ", "=");

    if (params == "")
      return false;
    command << params;
    command << fmt::format("WHERE id = {}", entity.id);

    auto *hldb_impl = this->parent()->parent();
    return !hldb_impl->raw_query(command.str());
  }

  bool
  employee_manipulator::remove(int id) const noexcept
  {
    std::string command =
      fmt::format("DELETE from employees WHERE id = {}", id);
    auto *hldb_impl = this->parent()->parent();
    return !hldb_impl->raw_query(command);
  }

  data_access_manager *
  employee_manipulator::parent() const noexcept
  {
    return container_of(this, data_access_manager, m_employee_manipulator);
  }

  std::string
  employee_manipulator::glue_params(const employee_t &entity,
                                    std::string_view separator,
                                    std::string_view eq) const noexcept
  {
    std::stringstream params;
    bool concat = false;
    if (!sql::any(entity.name)) {
      params << fmt::format(" name {} \'{}\'", eq, entity.name);
      concat = true;
    }

    if (!sql::any(entity.surname)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" surname {} \'{}\' ", eq, entity.surname);
    }

    if (!sql::any(entity.hire_date)) {
      auto date = str2base_str(epoch2str(entity.hire_date));
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(
        " hire_date = STR_TO_DATE(\'{}\',\'%d.%m.%y\') ", date);
    }

    if (!sql::any(entity.salary)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" salary {} {} ", eq, entity.salary);
    }

    if (!sql::any(entity.email)) {
      if (concat)
        params << fmt::format(" {} ", separator);
      else
        concat = true;
      params << fmt::format(" email {} \'{}\' ", eq, entity.email);
    }

    if (!sql::any(entity.phone_number)) {
      if (concat)
        params << fmt::format(" {} ", separator);

      params << fmt::format(" phone_number {} \'{}\' ",
                            eq,
                            entity.phone_number);
    }
    return params.str();
  }

} // namespace app::dbaccess
