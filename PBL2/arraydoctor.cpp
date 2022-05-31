#include "arraydoctor.h"

arrayDoctor::arrayDoctor()
{
    this->data = nullptr;
    this->n = 0;
}

arrayDoctor::~arrayDoctor()
{
    delete[] this->data;
}

int arrayDoctor::length()
{
    return this->n;
}

void arrayDoctor::add(const doctor& d)
{
    doctor *tmpt = new doctor[this->n];
    for(int i = 0; i < this->n ; i++){
        tmpt[i] = this->data[i];
    }
    delete[] this->data;
    this->data = new doctor[this->n + 1];
    for(int i = 0; i < this->n; i++){
        this->data[i] = tmpt[i];
    }
    this->data[n] = d;
    delete[] tmpt;
    this-> n++;
}

int arrayDoctor::find(QString id)
{
    for(int i = 0; i < this->n; i++){
        if(this->data[i].getId() == id){
            return i;
        }
    }
    return -1;
}

doctor& arrayDoctor::operator[](int i)
{
    return this->data[i];
}
