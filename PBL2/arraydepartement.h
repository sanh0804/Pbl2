#ifndef ARRAYDEPARTEMENT_H
#define ARRAYDEPARTEMENT_H

#include "departement.h"
class arrayDepartement
{
private:
    departement *data;
    int n;
public:
    arrayDepartement();
    ~arrayDepartement();

    int length();
    void add(const departement &);
    departement& operator[](const int);
};

#endif // arrayDepartement_H
