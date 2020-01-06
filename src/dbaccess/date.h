#pragma once

#include <chrono>
#include <string>
namespace app::dbaccess {

using tb = std::chrono::milliseconds;
using date_t = std::chrono::time_point<std::chrono::system_clock, tb>;
date_t str2epoch(const char* date);
std::string epoch2str(const date_t&);
std::string str2base_str(std::string &s);
std::string str2base_str(std::string &&s);
}
