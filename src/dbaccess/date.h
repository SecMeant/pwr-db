#pragma once

#include <chrono>
#include <string>
namespace app::dbaccess {
using date_t = std::chrono::time_point<std::chrono::system_clock>;
using duration_t = std::chrono::duration<unsigned int, std::milli>;
date_t str2epoch(const char* date, const char* format);
std::string epoch2str(const date_t&);
}
