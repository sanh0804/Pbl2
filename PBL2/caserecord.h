#ifndef CASERECORD_H
#define CASERECORD_H

#include <QString>
class caseRecord
{
private:
    QString caseRecordId, patientId;
    float height, weight;
    QString health, dateMake, dateBack, listMedicine;

public:
    caseRecord(QString = "", QString = "", float = 0, float = 0, QString = "", QString = "", QString = "", QString = "");
    ~caseRecord();

    QString getCaseRecordId();
    QString getPatientId();
    float getHeight();
    float getWeight();
    QString getHealth();
    QString getDateMake();
    QString getDateBack();
    QString getListMedicine();

    void setCaseRecordId(QString);
    void setPatientId(QString);
    void setHeight(float);
    void setWeight(float);
    void setHealth(QString);
    void setDateMake(QString);
    void setDateBack(QString);
    void setListMedicine(QString);
};

#endif // CASERECORD_H
