#include "arrayDepartement.h"

arrayDepartement::arrayDepartement()
{
    this->data = nullptr;
    this->n = 0;
}

arrayDepartement::~arrayDepartement()
{
    delete[] this->data;
}

int arrayDepartement::length()
{
    return this->n;
}

void arrayDepartement::add(const departement & dp)
{
    departement *tmpt = new departement[this->n];
    for(int i = 0; i < this->n ; i++){
        tmpt[i] = this->data[i];
    }
    delete[] this->data;
    this->data = new departement[this->n + 1];
    for(int i = 0; i < this->n; i++){
        this->data[i] = tmpt[i];
    }
    this->data[n] = dp;
    delete[] tmpt;
    this-> n++;
}

departement& arrayDepartement::operator[](const int index){
    return this->data[index];
}
