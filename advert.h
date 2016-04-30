#ifndef ADVERT_H
#define ADVERT_H

#include <QString>

using namespace std;

class Advert
{
    QString type;
    QString num;
    QString street;
    QString city;
    QString zip;
    QString description;
    int size;
    int rooms;
    int price;
    int id;
public:
    Advert();
    Advert(QString type, QString num, QString street, QString city, QString zip, QString description, int size, int rooms, int price);
    int GetId();
    void SetId(int id);
    QString GetType();
    void SetType(QString type);
    QString GetNum();
    void SetNum(QString num);
    QString GetStreet();
    void SetStreet(QString street);
    QString GetCity();
    void SetCity(QString city);
    QString GetZip();
    void SetZip(QString zip);
    QString GetDescription();
    void SetDescription(QString description);
    int GetSize();
    void SetSize(int size);
    int GetRooms();
    void SetRooms(int rooms);
    int GetPrice();
    void SetPrice(int price);
};

#endif // ADVERT_H
