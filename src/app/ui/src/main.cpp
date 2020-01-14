#include "mainwindow.h"
#include "hldb.h"
#include "dbaccess/db_defaults.h"
#include <QApplication>

using namespace app;
using namespace app::logic;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  hldb h(dbaccess::defaults::DB_DATABASE);

  MainWindow w(h);
  w.show();

  return a.exec();
}
