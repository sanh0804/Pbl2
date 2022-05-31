#ifndef BED_H
#define BED_H

#include "departement.h"
#include "room.h"
class bed: public room
{
    private:
        QString bedId;
        bool bedStatus;
        QString patientId;
    public:
        bed(QString = "", bool = 1, QString = "", QString = "", QString = "", int = 0, QString = "", QString = "");
        ~bed();

        QString getBedId();
        bool getBedStatus();
        QString getPatientId();

        void setBedId(QString);
        void setBedStatus(bool);
        void setPatientId(QString);
};

#endif // BED_H
