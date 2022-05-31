#include "caserecord.h"

caseRecord::caseRecord(QString caseRecordId, QString patientId, float height, float weight, QString health, QString dateMake, QString dateBack, QString listMedicine)
    :caseRecordId(caseRecordId), patientId(patientId), height(height), weight(weight), health(health), dateMake(dateMake), dateBack(dateBack), listMedicine(listMedicine)
{

}

caseRecord::~caseRecord()
{

}

QString caseRecord::getCaseRecordId()
{
    return this->caseRecordId;
}

QString caseRecord::getPatientId()
{
    return this->patientId;
}

float caseRecord::getHeight()
{
    return this->height;
}

float caseRecord::getWeight()
{
    return this->weight;
}

QString caseRecord::getHealth()
{
    return this->health;
}

QString caseRecord::getDateMake()
{
    return this->dateMake;
}

QString caseRecord::getDateBack()
{
    return this->dateBack;
}

QString caseRecord::getListMedicine()
{
    return this->listMedicine;
}

void caseRecord::setCaseRecordId(QString caseRecordId)
{
    this->caseRecordId = caseRecordId;
}

void caseRecord::setPatientId(QString patientId)
{
    this->patientId = patientId;
}

void caseRecord::setHeight(float height)
{
    this->height = height;
}

void caseRecord::setWeight(float weight)
{
    this->weight = weight;
}

void caseRecord::setHealth(QString health)
{
    this->health = health;
}

void caseRecord::setDateMake(QString dateMake)
{
    this->dateMake = dateMake;
}

void caseRecord::setDateBack(QString dateBack)
{
    this->dateBack = dateBack;
}

void caseRecord::setListMedicine(QString listMedicine)
{
    this->listMedicine = listMedicine;
}


