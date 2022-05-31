#include "doctor.h"
#include "departement.h"
doctor::doctor(QString id, QString name, int age, QString gender, QString address, QString number, QString departementId, QString departementName)
    :people(id, name, age, gender, address, number), departement(departementId, departementName)
{
}

doctor::~doctor()
{

}
