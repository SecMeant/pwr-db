#include "login_popup.h"
#include "ui_login_popup.h"
#include <cstdlib>
#include <QDebug>
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
    qDebug() << "Login: " << this->ui->username->text() << ", pass: " <<this->ui->password->text();
    auth_status = logic.authenticate(this->ui->username->text().toStdString(), this->ui->password->text().toStdString());
    qDebug() << "Stat: " << auth_status;
}

void login_popup::on_dialogButtonBox_rejected()
{
    auth_status = true;
//    exit(0);
}
