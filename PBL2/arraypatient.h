#ifndef ARRAYPATIENT_H
#define ARRAYPATIENT_H

#include <patient.h>
class arrayPatient
{
private:
    patient *data;
    int n;
public:
    arrayPatient();
    ~arrayPatient();
    int length();
    void add(const patient&);
    int find(const QString);
    patient& operator[](const int);
};

#endif // ARRAYPATIENT_H
