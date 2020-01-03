#include "date.h"
#include <ctime>
#include <sstream>
#include <fmt/format.h>
#include <iomanip>

using std::chrono::duration;
namespace app::dbaccess {
  date_t str2epoch(const char* date, const char* format)
  {
    std::stringstream ss(date);
    std::tm dt;
    ss >> std::get_time(&dt, format);
    std::time_t tt = std::mktime(&dt);
    return date_t(duration_t(tt*60));
  }

  std::string epoch2str(const date_t& date)
  {
    auto rawtime =  std::chrono::system_clock::to_time_t(date)/60;
    struct tm * ptm;
    ptm = gmtime ( &rawtime );
    return fmt::format("{}.{}.{}", ptm->tm_year, ptm->tm_mon,ptm->tm_mday);
  }
}