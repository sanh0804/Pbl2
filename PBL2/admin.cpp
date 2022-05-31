#include "admin.h"
admin::admin(QString doctorID, QString username, QString password)
    :doctorID(doctorID), username(username), password(password)
{

}

admin::~admin()
{

}

QString admin::getDoctorId()
{
    return this->doctorID;
}

QString admin::getUsername()
{
    return this->username;
}

QString admin::getPassword()
{
    return this->password;
}
