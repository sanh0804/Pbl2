#include "people.h"
people::people(QString id, QString name, int age, QString gender, QString address, QString number)
    :id(id), name(name), age(age), gender(gender), address(address), number(number)
{
}

people::~people()
{
}

QString people::getId()
{
    return this->id;
}

QString people::getName()
{
    return this->name;
}

int people::getAge()
{
    return this->age;
}

QString people::getGender()
{
    return this->gender;
}

QString people::getAddress()
{
    return this->address;
}

QString people::getNumber()
{
    return this->number;
}

void people::setId(QString id)
{
    this->id = id;
}

void people::setName(QString name)
{
    this->name = name;
}

void people::setAge(int age)
{
    this->age = age;
}

void people::setGender(QString gender)
{
    this->gender = gender;
}

void people::setAddress(QString address)
{
    this->address = address;
}

void people::setNumber(QString number)
{
    this->number = number;
}
