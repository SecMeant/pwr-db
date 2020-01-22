#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hldb.h"
#include <memory>
//#include <QBarSeries>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(app::logic::hldb_i &hldb, QWidget *parent = nullptr);
  ~MainWindow();
    void low_privilege_setup();

    void high_privilege_setup();

private slots:
    void on_customer_id_textChanged(const QString &arg1);

    void on_customer_add_released();

    void on_customer_search_released();

    void on_customer_results_cellClicked(int row, int column);

    void on_offer_id_textChanged(const QString &arg1);

    void on_offer_add_released();

    void on_offer_search_released();

    void on_offer_results_cellClicked(int row, int column);

    void on_tour_insurance_toggled(bool checked);

    void on_tour_id_textChanged(const QString &arg1);

    void on_tour_extra_meals_toggled(bool checked);

    void on_tour_search_released();

    void on_tour_resign_released();

    void on_tour_results_cellClicked(int row, int column);

    void on_employee_id_textChanged(const QString &arg1);

    void on_employee_add_released();

    void on_employee_search_released();

    void on_employee_results_cellClicked(int row, int column);

    void on_tour_modify_released();

    void on_logout_released();

    void on_new_tour_customer_search_released();

    void on_new_tour_buy_released();

    void on_new_tour_offer_search_released();

    void on_new_tour_customer_id_textChanged(const QString &arg1);

    void on_new_tour_offer_id_textChanged(const QString &arg1);

    void on_new_tour_customer_results_cellClicked(int row, int column);

    void on_new_tour_offer_results_cellClicked(int row, int column);

    void on_new_tour_with_insurance_toggled(bool checked);

    void on_new_tour_with_extra_meals_toggled(bool checked);

    void on_annual_income_draw_chart_released();

    void on_tour_draw_chart_released();

    void on_choose_year_currentIndexChanged(const QString &arg1);

private:
  Ui::MainWindow *ui;
  app::logic::hldb_i &logic;
//  std::unique_ptr<QBarSeries> series;
//  std::vector<QBarSet> months;
};

#endif // MAINWINDOW_H
