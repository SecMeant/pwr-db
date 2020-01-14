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
  w_login.exec();
  w.show();

  return a.exec();
}
