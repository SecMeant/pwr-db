#include <string>

namespace app::db_access {
  struct db_session
  {
  public:
    db_session() = delete;

    db_session(std::string username, std::string password)
      : username(std::move(username))
      , password(std::move(password))
    {}

    std::string username;
    std::string password;
  };
} // namespace app::db_access
