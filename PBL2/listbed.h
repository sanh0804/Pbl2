#ifndef LISTBED_H
#define LISTBED_H

#include "bed.h"
class listbed
{
private:
    bed *data;
    int n;
public:
    listbed();
    ~listbed();

    void add(const bed&);
};

#endif // LISTBED_H
