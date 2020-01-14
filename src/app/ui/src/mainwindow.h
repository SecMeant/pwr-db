#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
    void on_customer_id_textChanged(const QString &arg1);

    void on_customer_add_released();

    void on_customer_search_released();

    void on_customer_results_cellClicked(int row, int column);

    void on_offer_id_textChanged(const QString &arg1);

    void on_offer_add_released();

    void on_offer_search_released();

    void on_offer_results_cellClicked(int row, int column);

    void on_tour_customer_id_textChanged(const QString &arg1);

    void on_tour_customer_search_released();

    void on_tour_offer_id_textChanged(const QString &arg1);

    void on_tour_offer_search_released();

    void on_tour_customer_result_cellClicked(int row, int column);

    void on_tour_offer_result_cellClicked(int row, int column);

    void on_tour_with_insurance_toggled(bool checked);

    void on_tour_with_extra_melas_toggled(bool checked);

    void on_buy_tour_released();

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

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
