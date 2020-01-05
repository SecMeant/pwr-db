#include "offer_manager.h"
#include "../../reflect.h"
#include "../data_access_manager.h"
#include <sstream>

 #include <fmt/format.h>
namespace app::dbaccess
{
    std::vector<offer_t> offer_manager::get_all() noexcept
    {

      auto* db_conn = this->parent()->get_dbconn();
      auto res = db_conn->query_res("SELECT id,name,country,city,tickets_count,DATE_FORMAT(date_begin,'%d.%m.%Y'),DATE_FORMAT(date_end,'%d.%m.%Y'),price,categoryid,insurance_cost,extra_meals_cost from offers");

      offer_t offer;
      std::vector<offer_t> data{};
      if(res == nullptr)
        return data;
      for(uint i =0 ; i< res->row_count; i++)
      {
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

    std::vector<offer_t> offer_manager::get_like(const offer_t &entity) noexcept
    {
      std::stringstream command;
      command << "SELECT id,name,country,city,tickets_count,DATE_FORMAT(date_begin,'%d.%m.%Y'),DATE_FORMAT(date_end,'%d.%m.%Y'),price,categoryid,insurance_cost,extra_meals_cost from offers WHERE";

      auto params = glue_params(entity, " and ");

      offer_t offer;
      std::vector<offer_t> data{};

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

    offer_t offer_manager::get(int id) noexcept
    {
      auto* db_conn = this->parent()->get_dbconn();
      auto command = fmt::format("SELECT id,name,country,city,tickets_count,DATE_FORMAT(date_begin,'%d.%m.%Y'),DATE_FORMAT(date_end,'%d.%m.%Y'),price,categoryid,insurance_cost,extra_meals_cost from offers WHERE id = {}", id);
      auto res = db_conn->query_res(command);
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

    void offer_manager::add(const offer_t &entity) noexcept
    {
      std::string command = "INSERT INTO offers (name,country,city, date_begin, date_end, price, insurance_cost, extra_meals_cost, categoryid, tickets_count) VALUES (\'{}\', \'{}\', \'{}\', STR_TO_DATE(\'{}\',\'%d.%m.%y\'), STR_TO_DATE(\'{}\',\'%d.%m.%y\'), {}, {}, {}, {}, {})";
      command = fmt::format(command, entity.name, entity.country,entity.city,str2base_str(epoch2str(entity.date_begin)),str2base_str(epoch2str(entity.date_end)),  entity.price, entity.insurance_cost,entity.extra_meals_cost, entity.categoryid, entity.tickets_count);
      auto* db_conn = this->parent()->get_dbconn();
      db_conn->query_res(command);
    }

    void offer_manager::modify(const offer_t &entity) noexcept
    {
      std::stringstream command;
      command << "UPDATE offers SET";

      auto params = glue_params(entity, ", ");

      if(params == "")
        return;
      command << params;
      command << fmt::format("WHERE id = {}", entity.id);

      auto* db_conn = this->parent()->get_dbconn();
      db_conn->query_res(command.str());
    }

    void offer_manager::remove(const offer_t &entity) noexcept
    {
      std::stringstream command;
      command << "DELETE from offers WHERE";

      if(entity.id != 0)
        command << fmt::format(" id = {}", entity.id);
      else{
        auto params = glue_params(entity, " and ");

        if(params == "")
          return;
        command << params;
      }

      auto* db_conn = this->parent()->get_dbconn();
      db_conn->query_res(command.str());
    }

    data_access_manager*
    offer_manager::parent() noexcept
    {
      return container_of(this, data_access_manager, m_offer_manager);
    }

    std::string
    offer_manager::glue_params(const offer_t &entity, std::string separator) noexcept
    {
      std::stringstream params;
      bool concat = false;
      if(entity.name != "")
      {
        params << fmt::format(" name = \'{}\' ", entity.name);
        concat =true;
      }

      if(entity.country != "")
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" country = \'{}\' ", entity.country);
      }

      auto date = str2base_str(epoch2str(entity.date_begin));
      if(date != INVALID_DATE)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" date_begin = STR_TO_DATE(\'{}\',\'%d.%m.%y\') ", date);
      }

      date = str2base_str(epoch2str(entity.date_end));
      if(date != INVALID_DATE)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" date_end = STR_TO_DATE(\'{}\',\'%d.%m.%y\') ", date);
      }

      if(entity.price != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" price = {} ", entity.price);
      }

      if(entity.insurance_cost != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" insurance_cost = {} ", entity.insurance_cost);
      }

      if(entity.extra_meals_cost != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" extra_meals_cost = {} ", entity.extra_meals_cost);
      }

      if(entity.categoryid != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" categoryid = {} ", entity.categoryid);
      }

      if(entity.tickets_count != 0)
      {
        if(concat)
          params << fmt::format(" {} ",separator);
        else
          concat = true;
        params << fmt::format(" tickets_count = {} ", entity.tickets_count);
      }
      return params.str();
    }

}
