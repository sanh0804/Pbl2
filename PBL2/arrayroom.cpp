#include "arrayroom.h"

arrayRoom::arrayRoom()
{
    this->data = nullptr;
    this->n = 0;
}

arrayRoom::~arrayRoom()
{
    delete [] this->data;
}

int arrayRoom::length()
{
    return this->n;
}

int arrayRoom::find(QString id)
{
    for(int i = 0; i < this->length(); i++){
        if(this->data[i].getRoomId() == id){
            return i;
        }
    }
    return -1;
}
void arrayRoom::add(const room & r)
{
    room *tmpt = new room[this->n];
    for(int i = 0; i < this->n ; i++){
        tmpt[i] = this->data[i];
    }
    delete[] this->data;
    this->data = new room[this->n + 1];
    for(int i = 0; i < this->n; i++){
        this->data[i] = tmpt[i];
    }
    this->data[n] = r;
    delete[] tmpt;
    this-> n++;
}

room& arrayRoom::operator[](const int index){
    return this->data[index];
}
