#ifndef ARRAYDOCTOR_H
#define ARRAYDOCTOR_H

#include <doctor.h>
class arrayDoctor
{
private:
    doctor *data;
    int n;
public:
    arrayDoctor();
    ~arrayDoctor();

    int length();
    void add(const doctor&);
    int find(QString);
    doctor& operator[](int);
};

#endif // ARRAYDOCTOR_H
