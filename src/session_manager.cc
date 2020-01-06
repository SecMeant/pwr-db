#include "session_manager.h"

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

  static dbaccess::credentials_t
  get_users_hash(dbaccess::db_connection &conn, const std::string &username)
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

  static employee_id
  auth_(dbaccess::db_connection &dbconn, dbaccess::credentials_t &creds) noexcept
  {
    auto stored_creds = get_users_hash(dbconn, creds.login);

    if (!stored_creds.valid())
      return {};

    auto hash_match = stored_creds.pass_hash == creds.pass_hash;

    if (!hash_match)
      return {};

    creds.privilege = stored_creds.privilege;
    return employee_id(creds.employeeid);
  }

  bool
  session_manager::authenticate(dbaccess::credentials_t creds) noexcept
  {
    auto& dbconn = this->parent()->m_dbconn;
    this->m_state = state_t::logedout;
    this->m_privilege = privilege_level::none;

    if (!this->low_priv_auth())
      return false;

    auto empid = auth_(dbconn, creds);
    if (!empid.valid())
      return false;

    std::string *username;
    std::string *password;

    switch(creds.privilege) {
      case logic::privilege_level::high:
        username = &dbaccess::defaults::DB_USERNAME_HIPRIO;
        password = &dbaccess::defaults::DB_PASSWORD_HIPRIO;
        break;
      case logic::privilege_level::mid:
        username = &dbaccess::defaults::DB_USERNAME_MIPRIO;
        password = &dbaccess::defaults::DB_PASSWORD_MIPRIO;
        break;
      case logic::privilege_level::low:
        username = &dbaccess::defaults::DB_USERNAME_LOPRIO;
        password = &dbaccess::defaults::DB_PASSWORD_LOPRIO;
        break;
      case logic::privilege_level::none:
      default:
        return false;
    }

    this->m_session = this->parent()->get_employees_like(empid.get());

    if (!this->m_session.valid())
      return false;

    auto auth_status = dbconn.authenticate(*username, *password);

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
