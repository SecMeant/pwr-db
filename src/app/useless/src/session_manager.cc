#include "session_manager.h"

#include "dbaccess/table/credentials.h"
#include "hldb.h"
#include "privilege.h"

#include "dbaccess/db_defaults.h"

#include <fmt/format.h>

namespace app::logic {

  class employee_id
  {
  public:
    using id_type = int;
    static constexpr id_type INVALID_ID = -1;

    employee_id()
      : m_id(INVALID_ID)
    {}

    employee_id(int id)
      : m_id(id)
    {}

    inline bool
    valid() const noexcept
    {
      return this->m_id != INVALID_ID;
    }

    inline auto
    get() const noexcept
    {
      return this->m_id;
    }

  private:
    id_type m_id;
  };

  session_manager::session_manager(hldb_i &p)
    : parent(p)
  {}

  dbaccess::credentials_t
  session_manager::get_user_info(std::string_view username) noexcept
  {
    dbaccess::credentials_t creds;
    creds.login = username;
    sql::set_any(creds.id);
    sql::set_any(creds.employeeid);
    sql::set_any(creds.pass_hash);
    sql::set_any(creds.privilege);

    auto res = this->parent.get_credentials_like(creds);

    if (res.size() == 1)
      return res[0];
    return {};
  }

  dbaccess::credentials_t
  session_manager::auth_(std::string_view username,
                         std::string_view password) noexcept
  {
    auto stored_creds = this->get_user_info(username);

    if (!stored_creds.valid())
      return {};

    auto hash = this->parent.hash(password);
    auto hash_match = stored_creds.pass_hash == hash;

    if (!hash_match)
      return {};

    return stored_creds;
  }

  bool
  session_manager::authenticate(std::string_view username,
                                std::string_view password) noexcept
  {
    this->m_state = state_t::logedout;
    this->m_privilege = privilege_level::none;

    if (!this->low_priv_auth())
      return false;

    auto creds = auth_(username, password);
    if (!creds.valid())
      return false;

    std::string *dbusername;
    std::string *dbpassword;

    switch (creds.privilege) {
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

    this->m_session = this->parent.get_employees_like(creds.employeeid);

    if (!this->m_session.valid())
      return false;

    auto auth_status = this->parent.authenticate(*dbusername, *dbpassword);

    if (!auth_status)
      return false;

    this->m_state = state_t::logedin;
    this->m_privilege = creds.privilege;

    return true;
  }

  bool
  session_manager::set_privilege(dbaccess::employee_t employee,
                                 privilege_level priv) noexcept
  {
    if (this->m_privilege != privilege_level::high)
      return false;

    // TODO use data manipulator
    constexpr auto query_template =
      "UPDATE credentials SET privilege = \"{}\" WHERE id = \"{}\"";

    return this->parent.raw_query(
      fmt::format(query_template, static_cast<int>(priv), employee.id));

    // TODO check if changing privileges of current user, if so update it
    // also locally
  }

  bool
  session_manager::low_priv_auth() noexcept
  {
    return this->parent.authenticate(
      dbaccess::defaults::DB_USERNAME_LOPRIO,
      dbaccess::defaults::DB_PASSWORD_LOPRIO);
  }

} // namespace app::logic
