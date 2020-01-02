#pragma once

#include "dbaccess/db_connection.h"
#include "session_manager.h"
#include "dbaccess/data_access_manager.h"

namespace app::logic {

  class hldb
  {
  public:
    dbaccess::db_connection m_dbconn;
    session_manager m_session;
    dbaccess::data_access_manager db_access_manager;

  };
}
