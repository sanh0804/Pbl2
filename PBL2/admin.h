#ifndef ADMIN_H
#define ADMIN_H


#include <QString>
class admin
{
private:
    QString doctorID, username, password;
public:
    admin(QString = "", QString = "", QString = "");
    ~admin();

    QString getDoctorId();
    QString getUsername();
    QString getPassword();
};

#endif // ADMIN_H
