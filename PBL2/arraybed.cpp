#include "arrayBed.h"

arrayBed::arrayBed()
{
    this->data = nullptr;
    this->n = 0;
}

arrayBed::~arrayBed()
{
    delete [] this->data;
}

int arrayBed::length()
{
    return this->n;
}

void arrayBed::add(const bed & b){
    bed *tmpt = new bed[this->n];
    for(int i = 0; i < this->n ; i++){
        tmpt[i] = this->data[i];
    }
    delete[] this->data;
    this->data = new bed[this->n + 1];
    for(int i = 0; i < this->n; i++){
        this->data[i] = tmpt[i];
    }
    this->data[n] = b;
    delete[] tmpt;
    this-> n++;
}

int arrayBed::find(const QString id){
    for(int i = 0; i < this->n; i++){
        if(this->data[i].getBedId() == id){
            return i;
        }
    }
    return -1;
}

bed& arrayBed::operator[](const int index){
    return this->data[index];
}
