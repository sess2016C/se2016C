#ifndef USER_H
#define USER_H

#include <QString>
class User
{
public:
    User(int uID, bool admin, QString email, QString geb, QString name, QString vname, QString pwd);
    bool isAdmin();
    int getUID();
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
