#pragma once

#include <chrono>
#include <string>
namespace app::dbaccess {

  using tb = std::chrono::milliseconds;
  using date_t = std::chrono::time_point<std::chrono::system_clock, tb>;
  date_t
  str2epoch(const char *date);
  date_t
  str2epoch(const std::string &date);
  std::string
  epoch2str(const date_t &);
  std::string
  str2base_str(const std::string &s);
} // namespace app::dbaccess
