#ifndef DEPARTEMENT_H
#define DEPARTEMENT_H


#include <QString>
class departement
{
    private:
        QString departementId, departementName;
    public:
        departement(QString = "", QString = "");
        ~departement();

        QString getDepartementId();
        QString getDepartementName();

        void setDepartementId(QString);
        void setDepartementName(QString);
};

#endif // DEPARTEMENT_H
