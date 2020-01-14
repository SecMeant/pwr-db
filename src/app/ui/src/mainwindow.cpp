#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_customer_id_textChanged(const QString &arg1)
{

}

void MainWindow::on_customer_add_released()
{

}

void MainWindow::on_customer_search_released()
{

}

void MainWindow::on_customer_results_cellClicked(int row, int column)
{

}

void MainWindow::on_offer_id_textChanged(const QString &arg1)
{

}

void MainWindow::on_offer_add_released()
{

}

void MainWindow::on_offer_search_released()
{

}

void MainWindow::on_offer_results_cellClicked(int row, int column)
{

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
