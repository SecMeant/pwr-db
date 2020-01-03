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
     
      for(uint i =0 ; i< res->row_count; i++)
      {
        auto row = mysql_fetch_row(res.get());
        tour.id = atoi(row[0]);
        tour.debt = atoi(row[1]);
        tour.insurance = atoi(row[2]);
        tour.extra_meals = atoi(row[3]);
        tour.finished = atoi(row[4]);
        tour.customersid = atoi(row[5]);
        tour.employeesid = atoi(row[6]);
        tour.offerid = atoi(row[7]);
        tour.customerspesel = atoi(row[8]);
        tour.reserved_tickets = atoi(row[9]);
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

      
      for(uint i =0 ; i< res->row_count; i++)
      {
        auto row = mysql_fetch_row(res.get());
        tour.id = atoi(row[0]);
        tour.debt = atoi(row[1]);
        tour.insurance = atoi(row[2]);
        tour.extra_meals = atoi(row[3]);
        tour.finished = atoi(row[4]);
        tour.customersid = atoi(row[5]);
        tour.employeesid = atoi(row[6]);
        tour.offerid = atoi(row[7]);
        tour.customerspesel = atoi(row[8]);
        tour.reserved_tickets = atoi(row[9]);
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
      tour.finished = atoi(row[4]);
      tour.customersid = atoi(row[5]);
      tour.employeesid = atoi(row[6]);
      tour.offerid = atoi(row[7]);
      tour.customerspesel = atoi(row[8]);
      tour.reserved_tickets = atoi(row[9]);
      return tour;
    }

    void tour_manager::add(const tour_t &entity) noexcept
    {
      std::string command = "INSERT INTO biuro_podrozy.tour (customerpesel, employeeid, insurance, extra_meals, debt, finished, reserved_tickets)  VALUES ({}, {}, {}, {}, {}, {}, {})";
      command = fmt::format(command, entity.customerspesel,entity.employeesid,entity.insurance,entity.extra_meals,entity.debt,entity.finished,entity.reserved_tickets);
      auto* db_conn = this->parent()->get_dbconn();
      db_conn->query_res(command);
    }
    
    void tour_manager::modify(const tour_t &entity) noexcept
    {
      std::stringstream command;
      command << "UPDATE biuro_podrozy.tour SET";

      auto params = glue_params(entity, ", ");
      
      if(params == "")
        return;
      command << params;
      command << fmt::format("WHERE id = {}", entity.id);
      
      auto* db_conn = this->parent()->get_dbconn();
      db_conn->query_res(command.str());
    }
    
    void tour_manager::remove(const tour_t &entity) noexcept 
    {
      std::stringstream command;
      command << "DELETE from tour WHERE";
     
      auto params = glue_params(entity, " and ");
      
      if(params == "")
        return;
      command << params;
      command << fmt::format("WHERE id = {}", entity.id);

      auto* db_conn = this->parent()->get_dbconn();
      db_conn->query_res(command.str());
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
      if(entity.debt != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" debt = {} ", entity.debt);
      }
      
      if(entity.insurance != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" insurance = {} ", entity.insurance);
      }
       if(entity.extra_meals != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" extra_meals = {} ", entity.extra_meals);
      }

      if(entity.finished != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" finished = {} ", entity.finished);
      }

      if(entity.customersid != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" customersid = {} ", entity.customersid);
      }

      if(entity.employeesid != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" employeesid = {} ", entity.employeesid);
      }

      if(entity.offerid != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" offerid = {} ", entity.offerid);
      }

      if(entity.customerspesel != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" customerpesel = {} ", entity.customerspesel);
      }

      if(entity.reserved_tickets != 0)
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
