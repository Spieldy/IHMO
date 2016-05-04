#include "advert.h"

Advert::Advert() {
    id_client = -1;
}

Advert::Advert(QString type, QString num, QString street, QString city, QString zip, QString description, int isSaleRent, int size, int rooms, int price)
{
    this->isSaleRent = isSaleRent;
    this->type = type;
    this->num = num;
    this->street = street;
    this->city = city;
    this->zip = zip;
    this->description = description;
    this->size = size;
    this->rooms = rooms;
    this->price = price;
}

int Advert::GetId() {
    return id;
}

void Advert::SetId(int id) {
    this->id = id;
}

QDate Advert::GetDateCreation() {
    return date_creation;
}

void Advert::SetDateCreation(QDate date_creation) {
    this->date_creation = date_creation;
}

int Advert::GetIsSaleRent() {
    return isSaleRent;
}

void Advert::SetIsSaleRent(int isSaleRent) {
    this->isSaleRent = isSaleRent;
}

QString Advert::GetType() {
    return type;
}

void Advert::SetType(QString type) {
    this->type = type;
}

QString Advert::GetNum() {
    return num;
}

void Advert::SetNum(QString num) {
    this->num = num;
}

QString Advert::GetStreet() {
    return street;
}

void Advert::SetStreet(QString street) {
    this->street = street;
}

QString Advert::GetCity() {
    return city;
}

void Advert::SetCity(QString city) {
    this->city = city;
}

QString Advert::GetZip() {
    return zip;
}

void Advert::SetZip(QString zip) {
    this->zip = zip;
}

QString Advert::GetDescription() {
    return description;
}

void Advert::SetDescription(QString description) {
    this->description = description;
}

QString Advert::GetPhotoPrinc() {
    return photo_princ;
}

void Advert::SetPhotoPrinc(QString photo_princ) {
    this->photo_princ = photo_princ;
}

QString Advert::GetPhotoSup1() {
    return photo_sup1;
}

void Advert::SetPhotoSup1(QString photo_sup1) {
    this->photo_sup1 = photo_sup1;
}

QString Advert::GetPhotoSup2() {
    return photo_sup2;
}

void Advert::SetPhotoSup2(QString photo_sup2) {
    this->photo_sup2 = photo_sup2;
}

QString Advert::GetPhotoSup3() {
    return photo_sup3;
}

void Advert::SetPhotoSup3(QString photo_sup3) {
    this->photo_sup3 = photo_sup3;
}

int Advert::GetSize() {
    return size;
}

void Advert::SetSize(int size) {
    this->size = size;
}

int Advert::GetRooms() {
    return rooms;
}

void Advert::SetRooms(int rooms) {
    this->rooms = rooms;
}

int Advert::GetPrice() {
    return price;
}

void Advert::SetPrice(int price) {
    this->price = price;
}

int Advert::GetIdClient()
{
    return id_client;
}

void Advert::SetIdClient(int value)
{
    id_client = value;
}
