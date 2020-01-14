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

private:
    Ui::login_popup *ui;
};

#endif // LOGIN_POPUP_H
