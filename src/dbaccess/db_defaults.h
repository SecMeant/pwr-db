#pragma once

#include <string>

namespace app::dbaccess::defaults {
  static constexpr auto DB_HOSTNAME = "localhost";
  static constexpr auto DB_USERNAME = "superuser";
  static constexpr auto DB_PASSWORD = "alamakota";
  static constexpr auto DB_DATABASE = "biuro_podrozy";
  static constexpr auto DB_PORT_NO = 3306;
  static constexpr auto DB_SOCKET = nullptr;
  static constexpr auto DB_OPT = 0;

  inline static std::string DB_USERNAME_HIPRIO = "hiprio";
  inline static std::string DB_PASSWORD_HIPRIO = "bazydanych19";
  inline static std::string DB_USERNAME_MIPRIO = "miprio";
  inline static std::string DB_PASSWORD_MIPRIO = "bazydanych19";
  inline static std::string DB_USERNAME_LOPRIO = "loprio";
  inline static std::string DB_PASSWORD_LOPRIO = "bazydanych19";
} // namespace app::dbaccess::defaults
