#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_popup.h"
#include "login_popup.h"
using namespace app;
using namespace app::logic;
using namespace app::dbaccess;

MainWindow::MainWindow(hldb_i &hldb, QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
, logic(hldb)
{
  ui->setupUi(this);

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_customer_id_textChanged(const QString &arg1)
{
  if (arg1.isEmpty())
    this->ui->customer_add->setText("Add");
  else
    this->ui->customer_add->setText("Modify");
}

static customer_t
customer_parse_info(Ui::MainWindow *ui)
{
  auto new_customer = customer_t::make_any();

  if (!ui->customer_id->text().isEmpty())
    new_customer.id = ui->customer_name->text().toInt();

  if (!ui->customer_name->text().isEmpty())
    new_customer.id = ui->customer_name->text().toInt();

  if (!ui->customer_surname->text().isEmpty())
    new_customer.id = ui->customer_surname->text().toInt();

  if (!ui->customer_email->text().isEmpty())
    new_customer.id = ui->customer_email->text().toInt();

  if (!ui->customer_pesel->text().isEmpty())
    new_customer.id = ui->customer_pesel->text().toInt();

  return new_customer;
}

void MainWindow::on_customer_add_released()
{
  auto new_customer = customer_parse_info(this->ui);

  if (sql::any(new_customer.id)) { // Add
    this->logic.add_customer(new_customer);
  } else { // Modify
    this->logic.modify_customer(new_customer);
  }

}

static void
customer_result_add_row(QTableWidget *table, const customer_t &customer)
{
  std::array<QTableWidgetItem *, customer_t::field_count> row;

  row[0] = new QTableWidgetItem(QString(customer.id));
  row[1] = new QTableWidgetItem(customer.name.c_str());
  row[2] = new QTableWidgetItem(customer.surname.c_str());
  row[3] = new QTableWidgetItem(customer.email.c_str());
  row[4] = new QTableWidgetItem(customer.pesel.c_str());

  auto row_index = table->rowCount();
  table->insertRow(row_index);

  for (auto i = 0ull; i < row.size(); ++i)
    table->setItem(row_index, i, row[i]);
}

void MainWindow::on_customer_search_released()
{
  auto new_customer = customer_parse_info(this->ui);

  auto customers = this->logic.get_customers_like(new_customer);

  this->ui->customer_results->clear();

  for (auto &c : customers)
    customer_result_add_row(this->ui->customer_results, c);
}

void MainWindow::on_customer_results_cellClicked(int row, int column)
{
  column = 0;
  auto item = this->ui->customer_results->item(row, column);
  this->ui->customer_id->setText(item->text());

  ++column;
  item = this->ui->customer_results->item(row, column);
  this->ui->customer_name->setText(item->text());

  ++column;
  item = this->ui->customer_results->item(row, column);
  this->ui->customer_surname->setText(item->text());

  ++column;
  item = this->ui->customer_results->item(row, column);
  this->ui->customer_email->setText(item->text());

  ++column;
  item = this->ui->customer_results->item(row, column);
  this->ui->customer_pesel->setText(item->text());
}

void MainWindow::on_offer_id_textChanged(const QString &arg1)
{
  if (arg1.isEmpty())
    this->ui->offer_add->setText("Add");
  else
    this->ui->offer_add->setText("Modify");
}

static offer_t
offer_parse_info(Ui::MainWindow *ui)
{
  auto new_offer = offer_t::make_any();

  if (!ui->offer_id->text().isEmpty())
    new_offer.id = ui->offer_name->text().toInt();

  if (!ui->offer_name->text().isEmpty())
    new_offer.name = ui->offer_name->text().toInt();

  if (!ui->offer_country->text().isEmpty())
    new_offer.country = ui->offer_country->text().toInt();

  if (!ui->offer_city->text().isEmpty())
    new_offer.city = ui->offer_city->text().toInt();

  if (!ui->offer_price->text().isEmpty())
    new_offer.price = ui->offer_price->text().toInt();

  if (!ui->offer_from->text().isEmpty())
    new_offer.date_begin = str2epoch(ui->offer_from->text().toStdString().c_str());

  if (!ui->offer_to->text().isEmpty())
    new_offer.date_end = str2epoch(ui->offer_to->text().toStdString().c_str());

  if (!ui->offer_insurance_cost->text().isEmpty())
    new_offer.insurance_cost = ui->offer_insurance_cost->text().toInt();

  if (!ui->offer_extra_meals_cost->text().isEmpty())
    new_offer.extra_meals_cost = ui->offer_extra_meals_cost->text().toInt();

  if (!ui->offer_ticket_count->text().isEmpty())
    new_offer.tickets_count = ui->offer_ticket_count->text().toInt();

  return new_offer;
}

void MainWindow::on_offer_add_released()
{
  auto new_offer = offer_parse_info(this->ui);

  if (sql::any(new_offer.id)) { // Add
    this->logic.add_offer(new_offer);
  } else { // Modify
    this->logic.modify_offer(new_offer);
  }

}

static void
offer_result_add_row(QTableWidget *table, const offer_t &offer, hldb_i &logic)
{
  std::array<QTableWidgetItem *, offer_t::field_count> row;

  row[0] = new QTableWidgetItem(QString(offer.id));
  row[1] = new QTableWidgetItem(offer.name.c_str());
  row[2] = new QTableWidgetItem(offer.country.c_str());
  row[3] = new QTableWidgetItem(offer.city.c_str());
  row[4] = new QTableWidgetItem(offer.price);
  row[5] = new QTableWidgetItem(epoch2str(offer.date_begin).c_str());
  row[6] = new QTableWidgetItem(epoch2str(offer.date_end).c_str());
  row[7] = new QTableWidgetItem(offer.insurance_cost);
  row[8] = new QTableWidgetItem(offer.extra_meals_cost);
  row[9] = new QTableWidgetItem(offer.tickets_count);
  row[10] = new QTableWidgetItem(logic.get_category_by_id(offer.categoryid).name.c_str());

  auto row_index = table->rowCount();
  table->insertRow(row_index);

  for (auto i = 0ull; i < row.size(); ++i)
    table->setItem(row_index, i, row[i]);
}

void MainWindow::on_offer_search_released()
{
  auto new_offer = offer_parse_info(this->ui);

  auto offers = this->logic.get_offers_like(new_offer);

  this->ui->offer_results->clear();

  for (auto &c : offers)
    offer_result_add_row(this->ui->offer_results, c, this->logic);
}

void MainWindow::on_offer_results_cellClicked(int row, int column)
{
  column = 0;
  auto item = this->ui->offer_results->item(row, column);
  this->ui->offer_id->setText(item->text());

  ++column;
  item = this->ui->offer_results->item(row, column);
  this->ui->offer_name->setText(item->text());

  ++column;
  item = this->ui->offer_results->item(row, column);
  this->ui->offer_country->setText(item->text());

  ++column;
  item = this->ui->offer_results->item(row, column);
  this->ui->offer_city->setText(item->text());

  ++column;
  item = this->ui->offer_results->item(row, column);
  this->ui->offer_price->setText(item->text());

  ++column;
  item = this->ui->offer_results->item(row, column);
  this->ui->offer_from->setText(item->text());

  ++column;
  item = this->ui->offer_results->item(row, column);
  this->ui->offer_to->setText(item->text());

  ++column;
  item = this->ui->offer_results->item(row, column);
  this->ui->offer_insurance_cost->setText(item->text());

  ++column;
  item = this->ui->offer_results->item(row, column);
  this->ui->offer_extra_meals_cost->setText(item->text());

  ++column;
  item = this->ui->offer_results->item(row, column);
  this->ui->offer_ticket_count->setText(item->text());
}

void MainWindow::on_tour_customer_id_textChanged(const QString &arg1)
{

}

void MainWindow::on_tour_customer_search_released()
{

}

void MainWindow::on_tour_offer_id_textChanged(const QString &arg1)
{

}

void MainWindow::on_tour_offer_search_released()
{

}

void MainWindow::on_tour_customer_result_cellClicked(int row, int column)
{

}

void MainWindow::on_tour_offer_result_cellClicked(int row, int column)
{

}

void MainWindow::on_tour_with_insurance_toggled(bool checked)
{

}

void MainWindow::on_tour_with_extra_melas_toggled(bool checked)
{

}

void MainWindow::on_buy_tour_released()
{

}

void MainWindow::on_tour_id_textChanged(const QString &arg1)
{

}


void MainWindow::on_tour_insurance_toggled(bool checked)
{

}

void MainWindow::on_tour_extra_meals_toggled(bool checked)
{

}

void MainWindow::on_tour_search_released()
{

}

void MainWindow::on_tour_resign_released()
{

}

void MainWindow::on_tour_results_cellClicked(int row, int column)
{

}

void MainWindow::on_employee_id_textChanged(const QString &arg1)
{

}

void MainWindow::on_employee_add_released()
{

}

void MainWindow::on_employee_search_released()
{

}

void MainWindow::on_employee_results_cellClicked(int row, int column)
{

}


void MainWindow::on_tour_modify_released()
{

}

void MainWindow::on_logout_released()
{
    this->setEnabled(false);
    login_popup w_login(logic);
    do{
      w_login.exec();
    }while(!w_login.get_login_status());
    this->setEnabled(true);
    if(logic.get_user_privilage() == privilege_level::high)
        high_privilege_setup();
    else
        low_privilege_setup();
}

void MainWindow::low_privilege_setup()
{
   this->ui->tabWidget->setTabEnabled(4,false);
}

void MainWindow::high_privilege_setup()
{
   this->ui->tabWidget->setTabEnabled(4,true);
}
