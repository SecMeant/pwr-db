#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_popup.h"
#include "login_popup.h"
#include <QDebug>
using namespace app;
using namespace app::logic;
using namespace app::dbaccess;

MainWindow::MainWindow(hldb_i &hldb, QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
, logic(hldb)
{
  ui->setupUi(this);
//  series = std::make_unique<QBarSeries>();
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
    new_customer.id = ui->customer_id->text().toInt();

  if (!ui->customer_name->text().isEmpty())
    new_customer.name = ui->customer_name->text().toStdString();

  if (!ui->customer_surname->text().isEmpty())
    new_customer.surname = ui->customer_surname->text().toStdString();

  if (!ui->customer_email->text().isEmpty())
    new_customer.email = ui->customer_email->text().toStdString();

  if (!ui->customer_pesel->text().isEmpty())
    new_customer.pesel = ui->customer_pesel->text().toStdString();

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

  row[0] = new QTableWidgetItem(QString::number(customer.id));
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

  this->ui->customer_results->setRowCount(0);

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
    new_offer.id = ui->offer_id->text().toInt();

  if (!ui->offer_name->text().isEmpty())
    new_offer.name = ui->offer_name->text().toStdString();

  if (!ui->offer_country->text().isEmpty())
    new_offer.country = ui->offer_country->text().toStdString();

  if (!ui->offer_city->text().isEmpty())
    new_offer.city = ui->offer_city->text().toStdString();

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

  row[0] = new QTableWidgetItem(QString::number(offer.id));
  row[1] = new QTableWidgetItem(offer.name.c_str());
  row[2] = new QTableWidgetItem(offer.country.c_str());
  row[3] = new QTableWidgetItem(offer.city.c_str());
  row[4] = new QTableWidgetItem(QString::number(offer.price));
  row[5] = new QTableWidgetItem(epoch2str(offer.date_begin).c_str());
  row[6] = new QTableWidgetItem(epoch2str(offer.date_end).c_str());
  row[7] = new QTableWidgetItem(QString::number(offer.insurance_cost));
  row[8] = new QTableWidgetItem(QString::number(offer.extra_meals_cost));
  row[9] = new QTableWidgetItem(QString::number(offer.tickets_count));
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

  this->ui->offer_results->setRowCount(0);

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

static customer_t
tour_customer_parse_info(Ui::MainWindow *ui)
{
  auto new_customer = customer_t::make_any();

  if (!ui->customer_id->text().isEmpty())
    new_customer.id = ui->customer_id->text().toInt();

  if (!ui->customer_name->text().isEmpty())
    new_customer.name = ui->customer_name->text().toStdString();

  if (!ui->customer_surname->text().isEmpty())
    new_customer.surname = ui->customer_surname->text().toStdString();

  if (!ui->customer_email->text().isEmpty())
    new_customer.email = ui->customer_email->text().toStdString();

  if (!ui->customer_pesel->text().isEmpty())
    new_customer.pesel = ui->customer_pesel->text().toStdString();

  return new_customer;
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

static tour_t
tour_parse_info(Ui::MainWindow *ui)
{
  tour_t tour = tour_t::make_any();

  if (!ui->tour_id->text().isEmpty())
    tour.id = ui->tour_id->text().toInt();

  if (!ui->tour_debt->text().isEmpty())
    tour.debt = ui->tour_debt->text().toInt();

  if (!ui->tour_state->text().isEmpty()) {
    auto state = static_cast<tour_state>(ui->tour_state->text().toInt());
    tour.state = valid(state) ? state : tour_state::ANY;
  }

  if (!ui->tour_customer_id->text().isEmpty())
    tour.customersid = ui->tour_customer_id->text().toInt();

  if (!ui->tour_employee_id->text().isEmpty())
    tour.employeesid = ui->tour_employee_id->text().toInt();

  if (!ui->tour_offer_id->text().isEmpty())
    tour.offerid = ui->tour_offer_id->text().toInt();

  if (!ui->tour_ticket_count->text().isEmpty())
    tour.reserved_tickets = ui->tour_ticket_count->text().toInt();

  return tour;
}

void MainWindow::on_tour_modify_released()
{
  tour_t tour = tour_parse_info(this->ui);
  this->logic.modify_tour(tour);
}

static void
tour_result_add_row(QTableWidget *table, const tour_t &tour)
{
  std::array<QTableWidgetItem *, tour_t::field_count> row;

  row[0] = new QTableWidgetItem(QString(tour.id));
  row[1] = new QTableWidgetItem(QString(tour.debt));
  row[2] = new QTableWidgetItem(QString(tour.insurance));
  row[3] = new QTableWidgetItem(QString(tour.extra_meals));
  row[4] = new QTableWidgetItem(QString(to_str(tour.state).c_str()));
  row[5] = new QTableWidgetItem(QString(tour.customersid));
  row[6] = new QTableWidgetItem(QString(tour.employeesid));
  row[7] = new QTableWidgetItem(QString(tour.offerid));
  row[8] = new QTableWidgetItem(QString(tour.reserved_tickets));

  auto row_index = table->rowCount();
  table->insertRow(row_index);

  for (auto i = 0ull; i < row.size(); ++i)
    table->setItem(row_index, i, row[i]);
}

void MainWindow::on_tour_search_released()
{
  tour_t tour = tour_parse_info(this->ui);
  auto tours = this->logic.get_tours_like(tour);

  this->ui->tour_results->setRowCount(0);

  for (auto &t : tours)
    tour_result_add_row(this->ui->tour_results, t);
}

void MainWindow::on_tour_resign_released()
{
  auto tour_itemlist = this->ui->tour_results->selectedItems();

  if (tour_itemlist.size() != tour_t::field_count)
    return;

  auto tour_id = tour_itemlist[0]->text().toInt();
  this->logic.drop_reservation(tour_id);
}

void MainWindow::on_tour_results_cellClicked(int row, int column)
{
  column = 0;
  auto item = this->ui->tour_results->item(row, column);
  this->ui->tour_id->setText(item->text());

  ++column;
  item = this->ui->tour_results->item(row, column);
  this->ui->tour_debt->setText(item->text());

  ++column;
  item = this->ui->tour_results->item(row, column);
  this->ui->tour_state->setText(item->text());

  ++column;
  item = this->ui->tour_results->item(row, column);
  this->ui->tour_customer_id->setText(item->text());

  ++column;
  item = this->ui->tour_results->item(row, column);
  this->ui->tour_employee_id->setText(item->text());

  ++column;
  item = this->ui->tour_results->item(row, column);
  this->ui->tour_offer_id->setText(item->text());

  ++column;
  item = this->ui->tour_results->item(row, column);
  this->ui->tour_ticket_count->setText(item->text());

  ++column;
  item = this->ui->tour_results->item(row, column);
  this->ui->tour_insurance->setChecked(item->text().toInt());

  ++column;
  item = this->ui->tour_results->item(row, column);
  this->ui->tour_extra_meals->setChecked(item->text().toInt());
}

void MainWindow::on_employee_id_textChanged(const QString &arg1)
{
  if (arg1.isEmpty())
    this->ui->employee_add->setText("Add");
  else
    this->ui->employee_add->setText("Modify");
}

static employee_t
employee_parse_info(Ui::MainWindow *ui)
{
  employee_t emp = employee_t::make_any();

  if (!ui->employee_id->text().isEmpty())
    emp.id = ui->employee_id->text().toInt();

  if (!ui->employee_name->text().isEmpty())
    emp.name = ui->employee_name->text().toStdString();

  if (!ui->employee_surname->text().isEmpty())
    emp.surname = ui->employee_surname->text().toStdString();

  if (!ui->employee_hiredate->text().isEmpty())
    emp.hire_date = str2epoch(ui->employee_hiredate->text().toStdString());

  if (!ui->employee_salary->text().isEmpty())
    emp.salary = ui->employee_salary->text().toInt();

  if (!ui->employee_phone->text().isEmpty())
    emp.phone_number = ui->employee_phone->text().toStdString();

  if (!ui->employee_email->text().isEmpty())
    emp.email = ui->employee_email->text().toStdString();

  return emp;
}

void MainWindow::on_employee_add_released()
{
  auto new_employee = employee_parse_info(this->ui);

  if (sql::any(new_employee.id)) { // Add
    this->logic.add_employee(new_employee);
  } else { // Modify
    this->logic.modify_employee(new_employee);
  }

}

static void
employee_result_add_row(QTableWidget *table, const employee_t &employee)
{
  std::array<QTableWidgetItem *, employee_t::field_count> row;

  row[0] = new QTableWidgetItem(QString(employee.id));
  row[1] = new QTableWidgetItem(employee.name.c_str());
  row[2] = new QTableWidgetItem(employee.surname.c_str());
  row[3] = new QTableWidgetItem(epoch2str(employee.hire_date).c_str());
  row[4] = new QTableWidgetItem(employee.salary);
  row[5] = new QTableWidgetItem(employee.phone_number.c_str());
  row[6] = new QTableWidgetItem(employee.email.c_str());

  auto row_index = table->rowCount();
  table->insertRow(row_index);

  for (auto i = 0ull; i < row.size(); ++i)
    table->setItem(row_index, i, row[i]);
}

void MainWindow::on_employee_search_released()
{
  auto new_employee = employee_parse_info(this->ui);

  auto employees = this->logic.get_employees_like(new_employee);

  this->ui->employee_results->setRowCount(0);

  for (auto &c : employees)
    employee_result_add_row(this->ui->employee_results, c);
}

void MainWindow::on_employee_results_cellClicked(int row, int column)
{
  column = 0;
  auto item = this->ui->employee_results->item(row, column);
  this->ui->employee_id->setText(item->text());

  ++column;
  item = this->ui->employee_results->item(row, column);
  this->ui->employee_name->setText(item->text());

  ++column;
  item = this->ui->employee_results->item(row, column);
  this->ui->employee_surname->setText(item->text());

  ++column;
  item = this->ui->employee_results->item(row, column);
  this->ui->employee_hiredate->setText(item->text());

  ++column;
  item = this->ui->employee_results->item(row, column);
  this->ui->employee_salary->setText(item->text());

  ++column;
  item = this->ui->employee_results->item(row, column);
  this->ui->employee_phone->setText(item->text());

  ++column;
  item = this->ui->employee_results->item(row, column);
  this->ui->employee_email->setText(item->text());
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
    this->ui->tabWidget->setTabEnabled(5,false);
}

void MainWindow::high_privilege_setup()
{
   this->ui->tabWidget->setTabEnabled(4,true);
    this->ui->tabWidget->setTabEnabled(5,true);
}

void MainWindow::on_new_tour_customer_search_released()
{
    auto new_customer = customer_parse_info(this->ui);

    auto customers = this->logic.get_customers_like(new_customer);

    this->ui->customer_results->setRowCount(0);

    for (auto &c : customers)
      customer_result_add_row(this->ui->new_tour_customer_results, c);
}

void MainWindow::on_new_tour_buy_released()
{
    auto customer_itemlist = this->ui->new_tour_customer_results->selectedItems();

    if (customer_itemlist.size() != customer_t::field_count)
      return;

    auto offer_itemlist = this->ui->new_tour_offer_results->selectedItems();

    if (offer_itemlist.size() != offer_t::field_count)
      return;

    auto customer_id = customer_itemlist[0]->text().toInt();
    auto offer_id = offer_itemlist[0]->text().toInt();
    auto ticket_count = this->ui->new_tour_tickets_number->text().toInt();
    auto insurance = this->ui->new_tour_with_insurance->isChecked();
    auto extra_meals = this->ui->new_tour_with_extra_meals->isChecked();

    this->logic.make_reservation(offer_id, customer_id, ticket_count, insurance, extra_meals);
}

void MainWindow::on_new_tour_offer_search_released()
{
    auto new_offer = offer_parse_info(this->ui);

    auto offers = this->logic.get_offers_like(new_offer);

    this->ui->offer_results->setRowCount(0);

    for (auto &c : offers)
      offer_result_add_row(this->ui->new_tour_offer_results, c, this->logic);
}

void MainWindow::on_new_tour_customer_id_textChanged(const QString &arg1)
{

}

void MainWindow::on_new_tour_offer_id_textChanged(const QString &arg1)
{

}

void MainWindow::on_new_tour_customer_results_cellClicked(int row, int column)
{
    column = 0;
    auto item = this->ui->customer_results->item(row, column);
    this->ui->tour_customer_id->setText(item->text());

    ++column;
    item = this->ui->customer_results->item(row, column);
    this->ui->new_tour_customer_name->setText(item->text());

    ++column;
    item = this->ui->new_tour_customer_results->item(row, column);
    this->ui->new_tour_customer_surname->setText(item->text());

    ++column;
    item = this->ui->new_tour_customer_results->item(row, column);
    this->ui->new_tour_customer_email->setText(item->text());

    ++column;
    item = this->ui->new_tour_customer_results->item(row, column);
    this->ui->new_tour_customer_pesel->setText(item->text());
}

void MainWindow::on_new_tour_offer_results_cellClicked(int row, int column)
{
    column = 0;
    auto item = this->ui->new_tour_offer_results->item(row, column);
    this->ui->new_tour_offer_id->setText(item->text());

    ++column;
    item = this->ui->new_tour_offer_results->item(row, column);
    this->ui->new_tour_offer_name->setText(item->text());

    ++column;
    item = this->ui->new_tour_offer_results->item(row, column);
    this->ui->new_tour_offer_country->setText(item->text());

    ++column;
    item = this->ui->new_tour_offer_results->item(row, column);
    this->ui->new_tour_offer_city->setText(item->text());

    ++column;
    item = this->ui->new_tour_offer_results->item(row, column);
    this->ui->new_tour_offer_price->setText(item->text());

    ++column;
    item = this->ui->new_tour_offer_results->item(row, column);
    this->ui->new_tour_offer_from->setText(item->text());

    ++column;
    item = this->ui->new_tour_offer_results->item(row, column);
    this->ui->new_tour_offer_to->setText(item->text());

    ++column;
    item = this->ui->new_tour_offer_results->item(row, column);
    this->ui->new_tour_offer_insurance_cost->setText(item->text());

    ++column;
    item = this->ui->new_tour_offer_results->item(row, column);
    this->ui->new_tour_offer_extra_meals_cost->setText(item->text());

    ++column;
    item = this->ui->new_tour_offer_results->item(row, column);
    this->ui->new_tour_offer_ticket_count->setText(item->text());
}

void MainWindow::on_new_tour_with_insurance_toggled(bool checked)
{

}

void MainWindow::on_new_tour_with_extra_meals_toggled(bool checked)
{

}

void MainWindow::on_annual_income_draw_chart_released()
{

}

void MainWindow::on_tour_draw_chart_released()
{

}

void MainWindow::on_choose_year_currentIndexChanged(const QString &arg1)
{

}
