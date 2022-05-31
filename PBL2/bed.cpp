#include "bed.h"

bed::bed(QString idBed, bool status, QString patientId, QString roomId, QString typeRoom, int numberBed, QString departementId, QString departementName)
    :room(roomId, typeRoom, numberBed, departementId, departementName)
{
    this->bedId = idBed;
    this->bedStatus = status;
    this->patientId = patientId;
}

bed::~bed()
{

}

QString bed::getBedId()
{
    return this->bedId;
}

bool bed::getBedStatus()
{
    return this->bedStatus;
}

QString bed::getPatientId()
{
    return this->patientId;
}

void bed::setBedId(QString bedId)
{
    this->bedId = bedId;
}

void bed::setBedStatus(bool bedStatus)
{
    this->bedStatus = bedStatus;
}

void bed::setPatientId(QString patientId)
{
    this->patientId = patientId;
}
