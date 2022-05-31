#include "patient.h"
patient::patient(QString id, QString name, int age, QString gender, QString address, QString number, bool hospitalize, QString typeOfBlood, float height, float weight)
    :people(id, name, age, gender, address, number)
{
    this->hospitalize = hospitalize;
    this->typeOfBlood = typeOfBlood;
    this->height = height;
    this->weight = weight;
}
patient::~patient()
{

}

bool patient::getHospitalize()
{
    return this->hospitalize;
}

QString patient::getTypeBlood()
{
    return this->typeOfBlood;
}

float patient::getHeight()
{
    return this->height;
}

float patient::getWeight()
{
    return this->weight;
}

void patient::setHospitalize(bool hospitalize)
{
    this->hospitalize = hospitalize;
}

void patient::setTypeBlood(QString typeBlood)
{
    this->typeOfBlood = typeBlood;
}

void patient::setHeight(float height)
{
    this->height = height;
}

void patient::setWeight(float weight)
{
    this->weight = weight;
}
