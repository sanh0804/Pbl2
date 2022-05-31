#ifndef PEOPLE_H
#define PEOPLE_H

#include <QString>
class people
{
private:
    QString id, name;
    int age;
    QString gender, address, number;
public:
    people(QString = "", QString = "", int = 0, QString = "", QString = "", QString = "");
    ~people();

    QString getId();
    QString getName();
    int getAge();
    QString getGender();
    QString getAddress();
    QString getNumber();

    void setId(QString);
    void setName(QString);
    void setAge(int);
    void setGender(QString);
    void setAddress(QString);
    void setNumber(QString);
};

#endif // PEOPLE_H
