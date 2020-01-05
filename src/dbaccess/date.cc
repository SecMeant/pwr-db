#include "date.h"
#include <ctime>
#include <sstream>
#include <fmt/format.h>
#include <iomanip>
#include <iostream>
using std::chrono::duration;
namespace app::dbaccess {
  date_t str2epoch(const char* date, const char* format)
  {
    std::stringstream ss(date);
    std::tm ptm {};
    ss >> std::get_time(&ptm, format);
    ptm.tm_year+=100;
    int64_t tt = std::mktime(&ptm)*1000;
    return date_t(Ms(tt));
  }

  std::string epoch2str(const date_t& date)
  {
    std::time_t t_c = std::chrono::system_clock::to_time_t(date);
    auto ptm = std::localtime(&t_c);
    return fmt::format("{:0>2}.{:0>2}.{:0>2}", ptm->tm_mday, ptm->tm_mon + 1,ptm->tm_year%100);
  }
}