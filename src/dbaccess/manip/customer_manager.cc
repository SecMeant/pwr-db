#include "customer_manager.h"
#include "../../reflect.h"
#include "../data_access_manager.h"
#include <sstream>
 #include <fmt/format.h>
namespace app::dbaccess 
{
    std::vector<customer_t> customer_manager::get_all() noexcept
    {

      auto* db_conn = this->parent()->get_dbconn();
      auto res = db_conn->query_res("SELECT * from customers");

      customer_t customer;
      std::vector<customer_t> data{};
      
      for(uint i =0 ; i< res->row_count; i++)
      {
        auto row = mysql_fetch_row(res.get());
        customer.id = atoi(row[0]);
        customer.name = row[1];
        customer.surname = row[2];
        customer.email = row[3];
        customer.pesel = row[4];
        data.push_back(customer);
      }
      return data;
    }

    std::vector<customer_t> customer_manager::get_like(const customer_t &entity) noexcept
    {
      std::stringstream command;
      command << "SELECT * from customers WHERE";
      bool concat = false; 

      if(entity.name != "")
      {
        command << fmt::format(" name = {} ", entity.name);
        concat =true;
      }

      if(entity.surname != "")
      {
        if(concat)
          command << fmt::format(" and ");
        else
          concat = true;
        command << fmt::format(" surname = {} ", entity.surname);
      }

      if(entity.email != "")
      {
        if(concat)
          command << fmt::format(" and ");
        else
          concat = true;
        command << fmt::format(" email = {} ", entity.email);
      }

      if(entity.pesel != "")
      {
        if(concat)
          command << fmt::format(" and ");
        else
         concat = true;
        command << fmt::format(" pesel = {} ", entity.pesel);
      }

      customer_t customer;
      std::vector<customer_t> data{};
      
      if(concat == false)
        return data;

      auto* db_conn = this->parent()->get_dbconn();
      auto res = db_conn->query_res(command.str());

      
      for(uint i =0 ; i< res->row_count; i++)
      {
        auto row = mysql_fetch_row(res.get());
        // FIXME row size and its contents depends on count and order of filtering
        // expressions in the query.
        customer.id = atoi(row[0]);
        customer.name = row[1];
        customer.surname = row[2];
        customer.email = row[3];
        customer.pesel = row[4];
        data.push_back(customer);
      }

      return data;
    }
    
    customer_t customer_manager::get(int id) noexcept 
    {
      auto* db_conn = this->parent()->get_dbconn();
      auto command = fmt::format("SELECT * from customers WHERE id = {}", id);
      auto res = db_conn->query_res(command);
      customer_t customer;
      if (!res || mysql_num_rows(res.get()) != 1)
       return customer;
      auto row = mysql_fetch_row(res.get());
      customer.id = id;
      customer.name = row[1];
      customer.surname = row[2];
      customer.email = row[3];
      customer.pesel = row[4];
      return customer;
    }
    
    void customer_manager::add(const customer_t &entity) noexcept
    {
      std::string command = "INSERT INTO biuro_podrozy.customers  (name,surname,email,pesel) VALUES ({} {} {} {})";
      command = fmt::format(command, entity.name, entity.surname, entity.email, entity.pesel);
      auto* db_conn = this->parent()->get_dbconn();
      db_conn->query_res(command);
    }
    
    void customer_manager::modify(const customer_t &entity) noexcept
    {
      std::stringstream command;
      command << "UPDATE biuro_podrozy.customers SET";
      bool concat = false;
      if(entity.name != "")
      {
        command << fmt::format(" name = {} ",entity.name);
        concat = true; 
      }

      if(entity.surname != "")
      {
        if(concat)
          command << ", ";
        else
          concat = true;
        command << fmt::format(" surname = {} ", entity.surname);
      }

      if(entity.email != "")
      {
        if(concat)
          command << ", ";
        else
          concat = true;
        command << fmt::format(" email = {} ", entity.email);
      }

      if(entity.pesel != "")
      {
        if(concat)
          command << ", ";
        else
          concat = true;
        command <<fmt::format(" pesel = {} ", entity.pesel);
      }

      if(concat == false)
        return;

      auto* db_conn = this->parent()->get_dbconn();
      db_conn->query_res(command.str());
    }
    
    void customer_manager::remove(const customer_t &entity) noexcept 
    {
      std::stringstream command;
      command << "DELETE from customers WHERE";
      bool concat = false; 

      if(entity.name != "")
      {
        command << fmt::format(" name = {} ", entity.name);
        concat =true;
      }

      if(entity.surname != "")
      {
        if(concat)
          command << fmt::format(" and ");
        else
          concat = true;
        command << fmt::format(" surname = {} ", entity.surname);
      }

      if(entity.email != "")
      {
        if(concat)
          command << fmt::format(" and ");
        else
          concat = true;
        command << fmt::format(" email = {} ", entity.email);
      }

      if(entity.pesel != "")
      {
        if(concat)
          command << fmt::format(" and ");
        command << fmt::format(" pesel = {} ", entity.pesel);
      }
      if(concat == false)
        return;
      auto* db_conn = this->parent()->get_dbconn();
      db_conn->query_res(command.str());
    }

    data_access_manager*
    customer_manager::parent() noexcept
    {
      return container_of(this, data_access_manager, m_customer_manager);
    }

}
