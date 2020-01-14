#include "mainwindow.h"
#include "hldb.h"
#include "dbaccess/db_defaults.h"
#include <QApplication>
#include "login_popup.h"

using namespace app;
using namespace app::logic;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  hldb h(dbaccess::defaults::DB_DATABASE);
  login_popup w_login(h);
  MainWindow w(h);
  do{
    w_login.exec();
  }while(!w_login.get_login_status());
  if(h.get_user_privilage() == privilege_level::high)
      w.high_privilege_setup();
  else
      w.low_privilege_setup();
  w.show();

  return a.exec();
}
