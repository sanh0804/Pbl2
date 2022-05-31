#ifndef ARRAYBED_H
#define ARRAYBED_H

#include "bed.h"
class arrayBed
{
private:
    bed *data;
    int n;
public:
    arrayBed();
    ~arrayBed();

    int length();

    void add(const bed&);
    int find(const QString);
    bed& operator[](const int);
};

#endif // arrayBed_H
