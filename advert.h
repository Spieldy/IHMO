#ifndef ADVERT_H
#define ADVERT_H

#include <QString>
#include <QDate>

using namespace std;

class Advert
{
    QString type;
    QString num;
    QString street;
    QString city;
    QString zip;
    QString description;
    QString photo_princ = "";
    QString photo_sup1 = "";
    QString photo_sup2 = "";
    QString photo_sup3 = "";
    QDate date_creation;
    int size;
    int rooms;
    int price;
    int id;
    int isSaleRent;
public:
    Advert();
    Advert(QString type, QString num, QString street, QString city, QString zip, QString description, int isSaleRent, int size, int rooms, int price);
    int GetId();
    void SetId(int id);
    int GetIsSaleRent();
    void SetIsSaleRent(int isSaleRent);
    QDate GetDateCreation();
    void SetDateCreation(QDate date_creation);
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
    QString GetPhotoPrinc();
    void SetPhotoPrinc(QString photo_princ);
    QString GetPhotoSup1();
    void SetPhotoSup1(QString photo_sup1);
    QString GetPhotoSup2();
    void SetPhotoSup2(QString photo_sup2);
    QString GetPhotoSup3();
    void SetPhotoSup3(QString photo_sup3);
    int GetSize();
    void SetSize(int size);
    int GetRooms();
    void SetRooms(int rooms);
    int GetPrice();
    void SetPrice(int price);
};

#endif // ADVERT_H
