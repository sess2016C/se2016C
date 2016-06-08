#include "newpassword.h"
#include "ui_newpassword.h"
#include "QString"
#include "global.h"

NewPassword::NewPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPassword)
{
    ui->setupUi(this);
}

NewPassword::~NewPassword()
{
    delete ui;
}

void NewPassword::on_btn_NpAendern_clicked()
{
    QString pw1 = ui->txt_NpPasswort1->text();
    QString pw2 = ui->txt_NpPasswort2->text();
    QString uName = user->getName();
    QString uVname = user->getVname();
    QString ugeb = user->getGeb();
    if(pw1 == pw2) {
        db->changeUserData(uName, uVname, pw1, ugeb);
        this->hide();
    } else {
        //TODO keine übereinstimmenden Passwörter
    }
}

void NewPassword::on_btn_ErAbbrechen_clicked()
{
    this->hide();
}
