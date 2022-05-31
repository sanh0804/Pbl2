#ifndef PATIENT_H
#define PATIENT_H

#include "people.h"
class patient: public people
{
    private:
        QString typeOfBlood;
        bool hospitalize;
        float height, weight;
    public:
        patient(QString id = "", QString name = "", int age = 0, QString gender = "", QString address = "", QString number = "", bool hospitalize = 0, QString typeOfBlood = "", float height = 0, float weight = 0);
        ~patient();

        bool getHospitalize();
        QString getTypeBlood();
        float getHeight();
        float getWeight();

        void setHospitalize(bool);
        void setTypeBlood(QString);
        void setHeight(float);
        void setWeight(float);
};

#endif // PATIENT_H
