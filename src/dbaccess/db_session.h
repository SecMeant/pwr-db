#pragma once

#include <string>

namespace app::dbaccess {
  struct db_session
  {
  public:
    db_session() = default;
    db_session(std::string username, std::string password)
      : username(std::move(username))
      , password(std::move(password))
    {}

    std::string get_password_hash() const noexcept
    {
      // TODO implement hashing
      return this->password;
    }

    std::string username;
    std::string password;
  };
} // namespace app::dbaccess
