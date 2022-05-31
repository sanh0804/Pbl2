#include "arrayadmin.h"
arrayAdmin::arrayAdmin()
{
    this->data = nullptr;
    this->n = 0;
}
arrayAdmin::~arrayAdmin()
{
    delete[] this->data;
}

int arrayAdmin::length()
{
    return this->n;
}

void arrayAdmin::add(const admin& ad)
{
    admin *tmpt = new admin[this->n];
    for(int i = 0; i < this->n ; i++){
        tmpt[i] = this->data[i];
    }
    delete[] this->data;
    this->data = new admin[this->n + 1];
    for(int i = 0; i < this->n; i++){
        this->data[i] = tmpt[i];
    }
    this->data[n] = ad;
    delete[] tmpt;
    this-> n++;
}

admin& arrayAdmin::operator[](int index)
{
    return this->data[index];
}
