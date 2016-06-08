#ifndef USER_H
#define USER_H

#include <QString>
class User
{
public:
    User(int uID, bool admin, QString email, QString geb, QString name, QString vname, QString pwd);
    bool isAdmin();
    int getUID();
    QString getEmail();
    QString getName();
    QString getVname();
    QString getPwd();
    QString getGeb();
    void setGeb(QString &geb);
    void setName(QString &name);
    void setVname(QString &Vname);
    void setPwd(QString &pwd);
private:
    int uID;
    bool admin;
    QString email;
    QString geb;
    QString name;
    QString vname;
    QString pwd;
};

#endif // USER_H
