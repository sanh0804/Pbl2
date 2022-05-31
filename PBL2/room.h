#ifndef ROOM_H
#define ROOM_H


#include "departement.h"
class room: public departement
{
    private:
        QString roomId, typeRoom;
        int numberBed;
    public:
        room(QString = "", QString = "", int = 0, QString = "", QString = "");
        ~room();

        QString getRoomId();
        QString getTypeRoom();
        int getNumberBed();

        void setRoomId(QString);
        void setTypeRoom(QString);
        void setNumberBed(int);
};

#endif // ROOM_H
