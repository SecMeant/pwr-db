#include "date.h"
#include <ctime>
#include <sstream>
#include <fmt/format.h>
#include <iomanip>
#include <iostream>
using std::chrono::duration;
constexpr int TIME_SINCE_EPOCH_BASE =1900;
constexpr int SEC_TO_MS =1000;
namespace app::dbaccess {
  date_t str2epoch(const char* date, const char* format)
  {
    std::stringstream ss(date);
    std::tm ptm {};
    ss >> std::get_time(&ptm, format);
    int64_t tt = std::mktime(&ptm)*SEC_TO_MS;
    if(tt < 0)
      return date_t(tb(0));
    return date_t(tb(tt));
  }

  std::string epoch2str(const date_t& date)
  {
    std::time_t t_c = std::chrono::system_clock::to_time_t(date);
    auto ptm = std::localtime(&t_c);
    return fmt::format("{:0>2}.{:0>2}.{:0>4}", ptm->tm_mday, ptm->tm_mon + 1,ptm->tm_year + TIME_SINCE_EPOCH_BASE);
  }

  std::string str2base_str(const char *s)
  {
    int day, mon, year;
    if (3 != sscanf(s, "%d.%d.%d;", &day, &mon, &year))
    {
      return "01.01.70";
    }
    return fmt::format("{:0>2}.{:0>2}.{:0>2}");
  }
}