#include "data_access_manager.h"
#include "../hldb.h"
#include "../reflect.h"
namespace app::dbaccess
{

  data_access_manager::data_access_manager()
  {
  }

  logic::hldb*
  data_access_manager::parent() noexcept
  {
    return container_of(this, logic::hldb, db_access_manager);
  }

  db_connection_i* data_access_manager::get_dbconn()
  {
    return &this->parent()->m_dbconn;
  }
}