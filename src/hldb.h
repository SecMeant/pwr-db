#pragma once

#include "dbaccess/db_connection.h"
#include "session_manager.h"

namespace app::logic {

  class hldb
  {
  public:
    dbaccess::db_connection m_dbconn;
    session_manager m_session;
  };
}
