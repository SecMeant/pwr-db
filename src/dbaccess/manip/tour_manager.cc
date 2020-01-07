#include "tour_manager.h"
#include "../../reflect.h"
#include "../data_access_manager.h"
#include <sstream>
 #include <fmt/format.h>
namespace app::dbaccess
{
    std::vector<tour_t> tour_manager::get_all() noexcept
    {

      auto* db_conn = this->parent()->get_dbconn();
      auto res = db_conn->query_res("SELECT * from tour");

      tour_t tour;
      std::vector<tour_t> data{};
      if(res == nullptr)
        return data;
      for(uint i =0 ; i< res->row_count; i++)
      {
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

    std::vector<tour_t> tour_manager::get_like(const tour_t &entity) noexcept
    {
      std::stringstream command;
      command << "SELECT * from tour WHERE";

      auto params = glue_params(entity, " and ");

      tour_t tour;
      std::vector<tour_t> data{};

      if(params == "")
        return data;
      command << params;


      auto* db_conn = this->parent()->get_dbconn();
      auto res = db_conn->query_res(command.str());
      if(res == nullptr)
        return data;

      for(uint i =0 ; i< res->row_count; i++)
      {
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

    tour_t tour_manager::get(int id) noexcept
    {
      auto* db_conn = this->parent()->get_dbconn();
      auto command = fmt::format("SELECT * from tour WHERE id = {}", id);
      auto res = db_conn->query_res(command);
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

    bool tour_manager::add(const tour_t &entity) noexcept
    {
      std::string command = "INSERT INTO tour (CustomerId, employeeid, offerid, insurance, extra_meals, debt, state, reserved_tickets)  VALUES ({}, {}, {}, {}, {}, {}, {}, {})";
      command = fmt::format(command, entity.customersid,entity.employeesid,entity.offerid, entity.insurance,entity.extra_meals,entity.debt,entity.state,entity.reserved_tickets);
      auto* db_conn = this->parent()->get_dbconn();
      return !db_conn->query_res(command);
    }

    bool tour_manager::modify(const tour_t &entity) noexcept
    {
      std::stringstream command;
      command << "UPDATE tour SET";

      auto params = glue_params(entity, ", ");

      if(params == "")
        return false;
      command << params;
      command << fmt::format("WHERE id = {}", entity.id);

      auto* db_conn = this->parent()->get_dbconn();
      return !db_conn->query_res(command.str());
    }

    bool tour_manager::remove(int id) noexcept
    {
      std::string command =fmt::format("DELETE from customers WHERE id = {}",id);
      auto* db_conn = this->parent()->get_dbconn();
      return !db_conn->query(command);
    }

    data_access_manager*
    tour_manager::parent() noexcept
    {
      return container_of(this, data_access_manager, m_tour_manager);
    }

    std::string
    tour_manager::glue_params(const tour_t &entity, std::string separator) noexcept
    {
      std::stringstream params;
      bool concat = false;
      if(!sql::any(entity.debt))
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" debt = {} ", entity.debt);
      }

      if(!sql::any(entity.insurance))
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" insurance = {} ", entity.insurance);
      }
      if(!sql::any(entity.extra_meals))
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" extra_meals = {} ", entity.extra_meals);
      }

      if(!sql::any(entity.state))
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" state = {} ", entity.state);
      }

      if(!sql::any(entity.customersid))
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" customerid = {} ", entity.customersid);
      }

      if(!sql::any(entity.employeesid))
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" employeeid = {} ", entity.employeesid);
      }

      if(!sql::any(entity.offerid))
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" offerid = {} ", entity.offerid);
      }

      if(!sql::any(entity.reserved_tickets))
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" reserved_tickets = {} ", entity.reserved_tickets);
      }

      return params.str();
    }

}
