#pragma once

#include <chrono>

namespace app::dbaccess {
using date_t = std::chrono::time_point<std::chrono::system_clock>;
}
