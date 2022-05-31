#ifndef ARRAYROOM_H
#define ARRAYROOM_H

#include "room.h"
class arrayRoom
{
private:
    room *data;
    int n;
public:
    arrayRoom();
    ~arrayRoom();

    int length();
    int find(QString);
    void add(const room&);
    room& operator[](const int);
};

#endif // ARRAYROOM_H
