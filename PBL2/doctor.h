#ifndef DOCTOR_H
#define DOCTOR_H


#include "people.h"
#include "departement.h"
class doctor: public people, public departement
{
public:
    doctor(QString id = "", QString name = "", int age = 0, QString gender = "", QString address = "", QString number = "", QString departementId = "", QString departementName = "");
    ~doctor();
};


#endif // DOCTOR_H
