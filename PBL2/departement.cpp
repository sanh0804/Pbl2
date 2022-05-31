#include "departement.h"
departement::departement(QString id, QString name)
    :departementId(id), departementName(name)
{

}

departement::~departement()
{

}

QString departement::getDepartementId()
{
    return this->departementId;
}

QString departement::getDepartementName()
{
    return this->departementName;
}

void departement::setDepartementId(QString id)
{
    this->departementId = id;
}

void departement::setDepartementName(QString name)
{
    this->departementName = name;
}
