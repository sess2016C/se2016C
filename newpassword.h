#ifndef NEWPASSWORD_H
#define NEWPASSWORD_H

#include <QDialog>

namespace Ui {
class NewPassword;
}

class NewPassword : public QDialog
{
    Q_OBJECT

public:
    explicit NewPassword(QWidget *parent = 0);
    ~NewPassword();

private slots:
    void on_btn_NpAendern_clicked();

    void on_btn_ErAbbrechen_clicked();

private:
    Ui::NewPassword *ui;
};

#endif // NEWPASSWORD_H
