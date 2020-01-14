#include "login_popup.h"
#include "ui_login_popup.h"

login_popup::login_popup(app::logic::hldb_i &hldb, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login_popup),
    logic(hldb)
{
    ui->setupUi(this);
}

login_popup::~login_popup()
{
    delete ui;
}

void login_popup::on_dialogButtonBox_accepted()
{
    auth_status = logic.authenticate(this->ui->username->text().toStdString(), this->ui->password->text().toStdString());
}

void login_popup::on_dialogButtonBox_rejected()
{
    QCoreApplication::quit();
}
