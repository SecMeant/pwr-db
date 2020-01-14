#ifndef LOGIN_POPUP_H
#define LOGIN_POPUP_H

#include <QDialog>

namespace Ui {
class login_popup;
}

class login_popup : public QDialog
{
    Q_OBJECT

public:
    explicit login_popup(QWidget *parent = nullptr);
    ~login_popup();

private slots:
    void on_dialogButtonBox_accepted();

    void on_dialogButtonBox_rejected();

private:
    Ui::login_popup *ui;
};

#endif // LOGIN_POPUP_H
