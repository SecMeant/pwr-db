#pragma once

#include "db_connection.h"

namespace app::dbaccess {
  struct da_manager
  {
    db_connection m_db_conn;
  };
}
