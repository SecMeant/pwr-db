#pragma once

#include <chrono>
#include <string>
namespace app::dbaccess {

using Ms = std::chrono::milliseconds;
using date_t = std::chrono::time_point<std::chrono::system_clock, Ms>;

date_t str2epoch(const char* date, const char* format);
std::string epoch2str(const date_t&);
}
