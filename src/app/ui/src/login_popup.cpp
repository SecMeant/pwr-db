#include "login_popup.h"
#include "ui_login_popup.h"

login_popup::login_popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login_popup)
{
    ui->setupUi(this);
}

login_popup::~login_popup()
{
    delete ui;
}
