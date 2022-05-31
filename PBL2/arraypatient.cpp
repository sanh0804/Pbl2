#include <arraypatient.h>

arrayPatient::arrayPatient()
{
    this->data = nullptr;
    this->n = 0;
}
arrayPatient::~arrayPatient(){
    delete[] this->data;
}

int arrayPatient::length()
{
    return this->n;
}

void arrayPatient::add(const patient & p){
    patient *tmpt = new patient[this->n];
    for(int i = 0; i < this->n ; i++){
        tmpt[i] = this->data[i];
    }
    delete[] this->data;
    this->data = new patient[this->n + 1];
    for(int i = 0; i < this->n; i++){
        this->data[i] = tmpt[i];
    }
    this->data[n] = p;
    delete[] tmpt;
    this-> n++;
}
int arrayPatient::find(const QString id){
    for(int i = 0; i < this->n; i++){
        if(this->data[i].getId() == id){
            return i;
        }
    }
    return -1;
}
patient& arrayPatient::operator[](const int index){
    return this->data[index];
}
