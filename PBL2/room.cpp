#include "room.h"
room::room(QString roomId, QString typeRoom, int numberBed, QString departementId, QString departementName)
    :departement(departementId, departementName)
{
    this->roomId = roomId;
    this->typeRoom = typeRoom;
    this->numberBed = numberBed;
}

room::~room()
{

}

QString room::getRoomId()
{
    return this->roomId;
}

QString room::getTypeRoom()
{
    return this->typeRoom;
}

int room::getNumberBed()
{
    return this->numberBed;
}

void room::setRoomId(QString roomId)
{
    this->roomId = roomId;
}

void room::setTypeRoom(QString typeRoom)
{
    this->typeRoom = typeRoom;
}

void room::setNumberBed(int numberBed)
{
    this->numberBed += numberBed;
}
