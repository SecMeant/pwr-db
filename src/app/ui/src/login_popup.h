#ifndef LOGIN_POPUP_H
#define LOGIN_POPUP_H

#include <QDialog>
#include "hldb.h"
#include "dbaccess/db_defaults.h"
namespace Ui {
class login_popup;
}

class login_popup : public QDialog
{
    Q_OBJECT

public:
    explicit login_popup(app::logic::hldb_i &hldb, QWidget *parent = nullptr);
    ~login_popup();

private slots:
    void on_dialogButtonBox_accepted();

    void on_dialogButtonBox_rejected();
    bool get_login_status(){return this->auth_status;}
private:
    Ui::login_popup *ui;
    bool auth_status = false;
    app::logic::hldb_i &logic;
};

#endif // LOGIN_POPUP_H
