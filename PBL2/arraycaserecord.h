#ifndef ARRAYCASERECORD_H
#define ARRAYCASERECORD_H

#include "caserecord.h"
class arrayCaseRecord
{
private:
    caseRecord *data;
    int n;
public:
    arrayCaseRecord();
    ~arrayCaseRecord();

    int length();

    void add(const caseRecord&);
    int findCaseRecordId(QString);
    int findPatientId(QString);
};

#endif // ARRAYCASERECORD_H
