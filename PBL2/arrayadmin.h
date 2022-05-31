#ifndef ARRAYADMIN_H
#define ARRAYADMIN_H


#include "admin.h"
class arrayAdmin
{
private:
    admin *data;
    int n;
public:
    arrayAdmin();
    ~arrayAdmin();
    int length();
    void add(const admin&);
    admin& operator[](int);
};

#endif // ARRAYADMIN_H
