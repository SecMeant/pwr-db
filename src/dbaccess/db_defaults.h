#pragma once

#include <string>

namespace app::dbaccess::defaults {
  static constexpr auto DB_HOSTNAME = "localhost";
  static constexpr auto DB_USERNAME = "root";
  static constexpr auto DB_PASSWORD = "alamakota";
  static constexpr auto DB_DATABASE = "biuro_podrozy";
  static constexpr auto DB_PORT_NO = 532227;
  static constexpr auto DB_SOCKET = nullptr;
  static constexpr auto DB_OPT = 0;

  inline static std::string DB_USERNAME_HIPRIO = "root";
  inline static std::string DB_PASSWORD_HIPRIO = "alamakota";
  inline static std::string DB_USERNAME_MIPRIO = "root";
  inline static std::string DB_PASSWORD_MIPRIO = "alamakota";
  inline static std::string DB_USERNAME_LOPRIO = "root";
  inline static std::string DB_PASSWORD_LOPRIO = "alamakota";
} // namespace app::dbaccess::defaults
