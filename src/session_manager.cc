#include "session_manager.h"

#include "dbaccess/table/credentials.h"
#include "hldb.h"
#include "privilege.h"
#include "reflect.h"

#include "dbaccess/db_defaults.h"

#include <fmt/format.h>

namespace app::logic {

  class employee_id
  {
  public:
    using id_type = int;
    static constexpr id_type INVALID_ID = -1;

    employee_id()
    : m_id(INVALID_ID) {}

    employee_id(int id)
    : m_id(id) {}

    inline bool
    valid() const noexcept
    { return this->m_id != INVALID_ID; }

    inline auto
    get() const noexcept
    { return this->m_id; }

  private:
    id_type m_id;
  };

  std::string
  session_manager::hash(std::string_view s) noexcept
  {
    auto& dbconn = this->parent()->m_dbconn;
    return session_manager::hash(dbconn, s);
  }

  std::string
  session_manager::hash(dbaccess::db_connection &dbconn, std::string_view s) noexcept
  {
    constexpr auto query_template = "select password('{}');";

    auto res = dbconn.query_res(fmt::format(query_template, s));

    if (!res)
      return "";

    return mysql_fetch_row(res.get())[0]+1;
  }

  static dbaccess::credentials_t
  get_user_info(dbaccess::db_connection &conn, std::string_view username)
  {
    //TODO use data manipulator
    constexpr auto query_template =
      "SELECT pass_hash, privilege, employeeid from credentials where login = \"{}\"";

    auto res = conn.query_res(fmt::format(query_template, username));

    dbaccess::credentials_t creds;

    if (!res || mysql_num_rows(res.get()) != 1)
      return creds;

    auto row = mysql_fetch_row(res.get());
    creds.login = username;
    creds.pass_hash = row[0];
    creds.privilege = static_cast<logic::privilege_level>(atoi(row[1]));
    creds.employeeid = atoi(row[2]);
    return creds;
  }

  static dbaccess::credentials_t
  auth_(dbaccess::db_connection &dbconn, std::string_view username,
        std::string_view password) noexcept
  {
    auto stored_creds = get_user_info(dbconn, username);

    if (!stored_creds.valid())
      return {};

    auto hash = session_manager::hash(dbconn, password);
    auto hash_match = stored_creds.pass_hash == hash;

    if (!hash_match)
      return {};

    return stored_creds;
  }

  bool
  session_manager::authenticate(std::string_view username, std::string_view password) noexcept
  {
    auto hdlb=this->parent();
    auto& dbconn = hdlb->m_dbconn;
    this->m_state = state_t::logedout;
    this->m_privilege = privilege_level::none;

    if (!this->low_priv_auth())
      return false;

    auto creds = auth_(dbconn, username, password);
    if (!creds.valid())
      return false;

    std::string *dbusername;
    std::string *dbpassword;

    switch(creds.privilege) {
      case logic::privilege_level::high:
        dbusername = &dbaccess::defaults::DB_USERNAME_HIPRIO;
        dbpassword = &dbaccess::defaults::DB_PASSWORD_HIPRIO;
        break;
      case logic::privilege_level::mid:
        dbusername = &dbaccess::defaults::DB_USERNAME_MIPRIO;
        dbpassword = &dbaccess::defaults::DB_PASSWORD_MIPRIO;
        break;
      case logic::privilege_level::low:
        dbusername = &dbaccess::defaults::DB_USERNAME_LOPRIO;
        dbpassword = &dbaccess::defaults::DB_PASSWORD_LOPRIO;
        break;
      case logic::privilege_level::none:
      default:
        return false;
    }

    this->m_session = hdlb->get_employees_like(creds.employeeid);

    if (!this->m_session.valid())
      return false;

    auto auth_status = dbconn.authenticate(*dbusername, *dbpassword);

    if (!auth_status)
      return false;

    this->m_state = state_t::logedin;
    this->m_privilege = creds.privilege;

    return true;
  }

  bool
  session_manager::set_privilege(dbaccess::employee_t employee, privilege_level priv) noexcept
  {
    if (this->m_privilege != privilege_level::high)
      return false;

    //TODO use data manipulator
    constexpr auto query_template =
      "UPDATE credentials SET privilege = \"{}\" WHERE id = \"{}\"";

    auto& dbconn = this->parent()->m_dbconn;
    return dbconn.query(fmt::format(query_template, static_cast<int>(priv), employee.id));

    //TODO check if changing privileges of current user, if so update it also locally
  }

  hldb*
  session_manager::parent() noexcept
  {
    return container_of(this, hldb, m_session);
  }

  bool
  session_manager::low_priv_auth() noexcept
  {
    auto& dbconn = this->parent()->m_dbconn;

    return dbconn.authenticate(dbaccess::defaults::DB_USERNAME_LOPRIO,
                               dbaccess::defaults::DB_PASSWORD_LOPRIO);
  }



}
